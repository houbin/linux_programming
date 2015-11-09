CXXFLAGS=-g -Wall -rdynamic -march=native
CXXFLAGS+=-O2

HEADERS=$(wildcard *.h)
TESTS= observe_test \
       observe_80_safe_test

all:$(TESTS)

${TESTS}: ${HEADERS}

${TESTS}:
	g++ ${CXXFLAGS} -o $@ $(filter %.cc,$^) ${LDFLAGS} -lpthread

observe_test: test/observe_test.cc

observe_80_safe_test: test/observe_80_safe_test.cc

clean:
	rm -f ${TESTS}
