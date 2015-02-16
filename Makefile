# Top level Makefile
include common.mk

# library and test, sources and dependencies
SRCS		:= $(wildcard *.cxx)
DEPS		:= $(patsubst %.cxx,.deps/%.d,$(SRCS))
TESTS		:= $(wildcard tests/test_*.cc)
TEST_DEPS	:= $(patsubst %.cc,.deps/%.d,$(TESTS))

.PHONY:	all tests clean distclean $(patsubst tests/%.cc,%,$(TESTS))

all:	libsfcore.so tests

libsfcore.so:	$(patsubst %.cxx,%.o,$(SRCS))
	$(CXX) $(LDFLAGS) -o $@ $^

tests:	$(patsubst %.cc,%,$(TESTS))
	@for t in $^; \
         do \
            $(TEST_RUN_HEADER) $$t; \
            LD_LIBRARY_PATH=. $$t --report_level=short; \
         done |& $(TEST_RUN_FILTER)

.deps .deps/tests:%:
	mkdir -p $@

$(DEPS):.deps/%.d:	%.cxx | .deps
	$(CXX) $(CXXSTD) -MM $< -MF $@

# do not include when cleaning
ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

$(patsubst %.cxx,%.o,$(SRCS)):%.o:	%.cxx
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(TEST_DEPS):.deps/%.d:	%.cc | .deps/tests
	$(CXX) $(CXXSTD) -I. -MM $< -MF $@

# not empty when target matches test* (condition is true)
ifneq ($(filter test%,$(MAKECMDGOALS)),)
-include $(TEST_DEPS)
endif

$(patsubst %.cc,%,$(TESTS)):%:	%.cc libsfcore.so
	$(CXX) $(CXXFLAGS) -I. -L. -lsfcore -o $@ $<

$(patsubst tests/%.cc,%,$(TESTS)):%:	tests/%
	@$(TEST_RUN_HEADER) $<
	@LD_LIBRARY_PATH=. $< $(args) --report_level=short |& $(TEST_RUN_FILTER)

clean:
	rm -f *.o *.so
	rm -f $(patsubst %.cc,%,$(TESTS))

distclean:	clean
	rm -rf .deps/
