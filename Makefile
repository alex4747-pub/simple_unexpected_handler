.PHONY: all test clean format tidy cpplint

STD=-std=c++11
CXXFLAGS = -g -O0 -I.
CFLAGS = $(CXXFLAGS) --ansi --pedantic

USE_GCC=

ifeq ($(USE_GCC),)
CXX = clang++
LIBS = -lc++
CC = clang
else
CXX = g++
LIBS = -lstdc++
CC = gcc
endif

FORMAT   = clang-format
CPPLINT = cpplint

SRCS = \
	simple_unexpected_handler.c

NCS = \
	simple_unexpected_handler.h


OBJS = $(patsubst %.c, %.o, $(SRCS))


all: $(OBJS)

%.o: %.c $(INCS)
	$(CC) -c $(CFLAGS) $<

test:
	cd test; $(MAKE) run-test

clean:
	rm -rf *~ *.o
	cd test; $(MAKE) clean

format:
	$(FORMAT) --style=google -i $(SRCS) $(INCS)
	cd test; $(MAKE) format

cpplint:
	$(CPPLINT) $(SRCS) $(INCS)
	cd test; $(MAKE) cpplint



