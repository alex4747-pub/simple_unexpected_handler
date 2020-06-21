STD=-std=c++11
CXXFLAGS = -g -O0 -I.. -I.
CFLAGS = $(CXXFLAGS) --ansi --pedantic

USE_GCC=yes

ifeq ($(USE_GCC),)
CXX = clang++
LIBS = -lc++
CC = clang
else
CXX = g++
LIBS = -lstdc++
CC = gcc
endif

FORMAT  = clang-format
CPPLINT = cpplint

SRCS = \
	test_main.cc

INCS = \
	../simple_unexpected_handler.h

CSRCS = \
	test_main_c.c

all: test_runner test_runner_std test_runner_c

simple_unexpected_handler.o: ../simple_unexpected_handler.c $(INCS)
	$(CC) -c $(CFLAGS) $<

test_runner: $(SRCS) $(INCS) simple_unexpected_handler.o Makefile
	$(CXX) -o $@ $(CXXFLAGS) $(SRCS) simple_unexpected_handler.o $(LIBS)

test_runner_std: $(SRCS) $(INCS) simple_unexpected_handler.o Makefile
	$(CXX) -o $@ $(CXXFLAGS) $(STD) $(SRCS) simple_unexpected_handler.o $(LIBS)

test_runner_c: $(CSRCS) $(INCS) simple_unexpected_handler.o Makefile
	$(CC) -o $@ $(CFLAGS) $(CSRCS) simple_unexpected_handler.o

format:
	$(FORMAT) --style=google -i $(SRCS) $(CSRCS) ../simple_unexpected_handler.c $(INCS)

cpplint:
	$(CPPLINT) $(SRCS) $(CSRCS) ../simple_unexpected_handler.c $(INCS)

clean:
	rm -rf test_runner* *~ *.dSYM *.o

run-test: test_runner test_runner_std test_runner_c
	@echo
	@echo "base test"
	./test_runner
	@echo
	@echo "C- test"
	./test_runner_c
	@echo



