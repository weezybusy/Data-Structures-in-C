.SUFFIXES: .c .h .o

SHELL    := /bin/bash
CC       := gcc
CFLAGS   := -g -std=c99 -Wall -Werror -Wextra -Wpedantic
SOURCES  := $(wildcard *.c)
INCLUDES := $(wildcard *.h)
OBJECTS  := $(SOURCES:.c=.o)
TARGET   := bstree

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@
	$(RM) $(OBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	$(RM) $(TARGET)
