CC = gcc

ifdef DEBUG
CDEBUG = -g
CFLAGS = -Wall -I$(IDIR) $(CDEBUG)
else
CFLAGS = -Wall -I$(IDIR)
endif

SDIR = ./src
SRCS_N = main.c
SRCS = $(patsubst %,$(SDIR)/%,$(SRCS_N))

LIBS = 

IDIR = ./include

DEPS_N =
DEPS = $(patsubst %,$(IDIR)/%,$(DEPS_N))


ODIR = ./obj
OBJS_N = main.o
OBJS = $(patsubst %,$(ODIR)/%,$(OBJS_N))

BDIR = ./bin
BIN = $(BDIR)/main

.PHONY: create_dirs clean

all: create_dirs $(BIN)

clean:
	@rm -rv $(ODIR) $(BDIR)

create_dirs:
	@mkdir -p $(ODIR) $(BDIR)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	@$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJS)
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
