PYTHON		:= $(shell which python)
PKGCONFIG	:= $(shell which pkg-config)

CC           	:= $(shell which gcc)
CXX 		:= $(shell which g++)

CSTD		:= -std=c++11
OPTS    	:= -g -Wall -fPIC -m64 $(CSTD)
CFLAGS  	:= -c -pthread $(OPTS)
LDFLAGS 	:= $(OPTS) -shared

SRCS		:= $(wildcard *.cxx)
DEPS		:= $(patsubst %.cxx,.deps/%.d,$(SRCS))
TESTS		:= $(wildcard tests/test_*.cc)
TEST_DEPS	:= $(patsubst %.cc,.deps/%.d,$(TESTS))


.PHONY:	all clean tests $(patsubst tests/%.cc,%,$(TESTS)) deps test-deps

libsfcore.so:	$(patsubst %.cxx,%.o,$(SRCS)) | deps
	$(CXX) $(LDFLAGS) -o $@ $^

deps:	.deps $(DEPS)

test-deps:	.deps/tests $(TEST_DEPS)

.deps .deps/tests:%:
	mkdir -p $@

$(DEPS):.deps/%.d:	%.cxx
	gcc $(CSTD) -MM $< -MF $@

-include $(DEPS)

$(patsubst %.cxx,%.o,$(SRCS)):%.o:	%.cxx
	$(CXX) $(CFLAGS) -o $@ $<

$(TEST_DEPS):.deps/%.d:	%.cc
	gcc $(CSTD) -I. -MM $< -MF $@

-include $(TEST_DEPS)

$(patsubst %.cc,%,$(TESTS)):%:	%.cc libsfcore.so
	$(CXX) -pthread $(OPTS) -I. -L. -lsfcore -o $@ $<

all:	libsfcore.so tests

clean:
	rm -f *.o *.so
	rm -f $(patsubst %.cc,%,$(TESTS))
	rm -f .deps/*.d .deps/tests/*.d


TEST_RUN_HEADER := echo -e "\e[1;32mTest\e[0m:"
TEST_RUN_FILTER := sed -e $$'s%error\|failed\|aborted%\033[1;31m&\033[0m%g'

tests:	$(patsubst %.cc,%,$(TESTS)) | test-deps
	@for t in $^; \
         do \
            $(TEST_RUN_HEADER) $$t; \
            LD_LIBRARY_PATH=. $$t --report_level=short; \
         done |& $(TEST_RUN_FILTER)

$(patsubst tests/%.cc,%,$(TESTS)):%:	tests/% | .deps/tests/%.d
	@$(TEST_RUN_HEADER) $<
	@LD_LIBRARY_PATH=. $< $(args) --report_level=short |& $(TEST_RUN_FILTER)
