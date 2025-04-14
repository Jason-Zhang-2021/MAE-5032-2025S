EXEC := foo
LIB  := libbar.a
DIR  := ./lib
SRC  := $(wildcard ./src/*.c)
OBJ  := $(patsubst ./src/%.c, %.o, $(SRC))

CFLAGS := -I./include
LDFLAGS := -L./lib
LDLIBS  := -lbar

CC := gcc
AR := ar rs
RM := rm -rf

%.o : ./src/%.c ./include/%.h
	$(CC) $(CFLAGS) -c $<

$(EXEC) : foo.c $(LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@ $^

$(LIB) : $(OBJ)
	$(AR) $@ $^

.PHONY: clean install
clean:
	$(RM) $(EXEC) $(OBJ) $(LIB) $(DIR)

install:
	mkdir -p $(DIR)
	mv $(LIB) $(DIR)

