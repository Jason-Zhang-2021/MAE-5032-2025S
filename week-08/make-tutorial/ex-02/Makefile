# Files
EXEC := foo
SRC  := bar.c foo.c
OBJ  := bar.o foo.o

# OPTIONS
CC      := gcc
CFLAGS  := -O3

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

foo.o bar.0: bar.h

# Useful phony targets
.PHONY: clobber clean neat echo
clobber: clean
	$(RM) $(EXEC)

clean: neat
	$(RM) $(OBJ)

neat:
	$(RM) *~ .*~

echo:
	@echo "Sources: $(SRC)"
	@echo "Objects: $(OBJ)"
