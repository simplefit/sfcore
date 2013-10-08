PYTHON		:= $(shell which python)
PKGCONFIG	:= $(shell which pkg-config)

CC           	:= $(shell which gcc)
CXX 		:= $(shell which g++)

OPTS    	:= -g -Wall -fPIC -m64
CFLAGS  	:= -c -pthread $(OPTS)
LDFLAGS 	:= $(OPTS) -shared

SRCS		:= $(wildcard *.cxx)
TESTS		:= $(wildcard tests/test_*.cc)


.PHONY:	all clean cleanall tests run

all:	libsfcore.so

libsfcore.so:	$(patsubst %.cxx,%.o,$(SRCS))
	$(CXX) $(LDFLAGS) -o $@ $^

$(patsubst %.cxx,%.o,$(SRCS)):%.o:	%.cxx
	$(CXX) $(CFLAGS) -o $@ $<

tests:	$(patsubst %.cc,%,$(TESTS))

$(patsubst %.cc,%,$(TESTS)):%:	%.cc libsfcore.so
	$(CXX) -pthread $(OPTS) -I. -L. -lsfcore -o $@ $<

run:	$(patsubst %.cc,%,$(TESTS))
	@for t in $^; do echo -e "\e[1mTest\e[0m: $$t"; LD_LIBRARY_PATH=. $$t; done
