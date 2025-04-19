# Define variables
EXEC = foo
LIB  = libbar.a

CC = gcc

ifneq ($(DEBUG_MODE), yes)
	CFLAGS = -O3 -MMD -MP
else
	CFLAGS = -g -MMD -MP
endif

SRC = $(wildcard ./src/*.c)
OBJ = $(patsubst ./src/%.c,%.o,$(SRC))

# Rules
$(EXEC): foo.c $(LIB)
	$(CC) -L./lib -I./include -o $@ $^ -lbar

$(LIB): $(OBJ)
	ar rs $@ $^

%.o: ./src/%.c ./include/%.h
	$(CC) $(CFLAGS) -I./include -c $<

# Phony targets
.PHONY: clean echo install
clean:
	@rm -rf *.o foo $(LIB)

echo:
	@echo $(SRC)
	@echo $(OBJ)

install:
	mkdir -p ./lib
	mv $(LIB) ./lib
