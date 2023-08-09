CC = gcc
LD = gcc

CFLAGS = -Wall -pipe 
OFLAGS = -c -I/usr/include
LFLAGS = $(CFLAGS) -L/usr/lib/

SRC_DIRS := ./engine

SOURCES = $(shell find $(SRC_DIRS) -name '*.c')
OBJECTS = $(SOURCES:.c=.o)

DEBUG = no
PROFILE = no
PEDANTIC = no
OPTIMIZATION = -O3

ifeq ($(DEBUG), yes)
	CFLAGS += -g
	OPTIMIZATION = -O0
endif

ifeq ($(PROFILE), yes)
	CFLAGS += -pg
endif

CFLAGS += $(OPTIMIZATION)

all: project

project: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o game

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRC_DIRS)/*.o game

rebuild: clean all

.PHONY : clean
.SILENT : clean