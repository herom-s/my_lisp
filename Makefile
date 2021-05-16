.POSIX:

include config.mk

all: create_dirs $(BIN)

clean:
	rm -rv $(ODIR) $(BDIR)

create_dirs:
	@mkdir -p $(ODIR) $(BDIR)

run:
	$(BIN)

debugg:
	$(DEBUGGER) $(BIN)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBS)

.PHONY: create_dirs clean
