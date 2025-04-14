# Files
EXEC := foo
SRC  := $(wildcard *.c) 
OBJ  := $(patsubst %.c,%.o,$(SRC))

# OPTIONS
CC      := gcc
CFLAGS  := -O3 -MMD -MP
LDFLAGS := -L/usr/lib
LDLIBS  := -lm

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

-include $(patsubst %.o, %.d, $(OBJ))

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
