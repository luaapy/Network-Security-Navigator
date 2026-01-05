# Simple Makefile for NSN
# Primary build system is CMake: mkdir build && cd build && cmake .. && make

CC ?= gcc
CFLAGS = -Wall -Wextra -IInclude -g
LDFLAGS = -lm -lpthread

# Quick find of sources (approximate for scaffolding)
SRCS = $(wildcard Nsn/*.c) \
       $(wildcard Objects/*.c) \
       $(wildcard Parser/*.c) \
       $(wildcard Modules/*.c) \
       $(wildcard Programs/*.c)

OBJS = $(SRCS:.c=.o)

TARGET = nsn

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test:
	./nsn examples/basic/01_hello_ping.nsn
