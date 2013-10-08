PYTHON		:= $(shell which python)
PKGCONFIG	:= $(shell which pkg-config)

CC           	:= $(shell which gcc)
CXX 		:= $(shell which g++)

OPTS    	:= -g -Wall -fPIC -m64
CFLAGS  	:= -c -pthread $(OPTS)
LDFLAGS 	:= $(OPTS) -shared

SRCS		:= $(wildcard *.cxx)
TESTS		:= $(wildcard tests/*.cc)


.PHONY:	all clean cleanall tests

all:	libsfcore.so

libsfcore.so:	$(patsubst %.cxx,%.o,$(SRCS))
	$(CXX) $(LDFLAGS) -o $@ $^

$(patsubst %.cxx,%.o,$(SRCS)):%.o:	%.cxx
	$(CXX) $(CFLAGS) -o $@ $<

tests:	$(patsubst %.cc,%,$(TESTS))

$(patsubst %.cc,%,$(TESTS)):%:	%.cc libsfcore.so
	$(CXX) -pthread $(OPTS) -I. -L. -lsfcore -o $@ $<
