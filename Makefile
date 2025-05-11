.POSIX:

CC = gcc
DEBUGGER = gdb
CFLAGS = -std=c99 -Wall -Wextra -pedantic -I$(IDIR)
CDEBUGFLAGS = -g2 -DDEBUG -O0
SDIR = src
IDIR = include
ODIR = obj
BDIR = bin
BIN = $(BDIR)/my_lisp

SRCS = $(wildcard $(SDIR)/*.c)
OBJS = $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

CFLAGS = -std=c99 -Wall -Wextra -pedantic -I$(IDIR) -O2

DEBUG ?= 0
ifeq ($(DEBUG),1)
	CFLAGS += $(CDEBUGFLAGS)
endif

RM = rm -f
RMDIR = rm -rf

all: $(BIN)

$(BIN): $(OBJS) | $(BDIR)
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(ODIR):
	@mkdir -p $@

$(BDIR):
	@mkdir -p $@

run: $(BIN)
	$(BIN)

debugg: $(BIN)
	$(DEBUGGER) $(BIN)

clean:
	$(RM) $(BIN)

cleanodir:
	$(RMDIR) $(ODIR)

cleanbdir:
	$(RMDIR) $(BDIR)

fclean: clean cleanodir cleanbdir

re: fclean all

-include $(DEPS)

.PHONY: all run debugg clean cleanodir cleanbdir fclean re