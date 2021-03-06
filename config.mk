CC = gcc

DEBUGGER = gdb
CDEBUG = -g2 -DDEBUG -O0 # Remember to remove debugg flags
CFLAGS = -std=c89 -Wall -Wextra  -pedantic -I$(IDIR) $(CDEBUG)

SDIR = ./src
SRCS_N = main.c parser.c lexer.c input.c eval.c print.c
SRCS = $(patsubst %,$(SDIR)/%,$(SRCS_N))

LIBS =
IDIR = ./include

DEPS_N = lexer.h parser.h eval.h input.h print.h
DEPS = $(patsubst %,$(IDIR)/%,$(DEPS_N))


ODIR = ./obj
OBJS_N = $(SRCS_N:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(OBJS_N))

BDIR = ./bin
BIN = $(BDIR)/main
