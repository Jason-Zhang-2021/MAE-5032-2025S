# Define variables
EXEC = foo

CC = gcc

ifneq ($(DEBUG_MODE), yes)
	CFLAGS = -O3 -MMD -MP
else
	CFLAGS = -g -MMD -MP
endif

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

# Rules
$(EXEC): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

-include $(patsubst %.c,%.d,$(SRC))

# Phony targets
.PHONY: clean echo
clean:
	@rm -rf *.o foo

echo:
	@echo $(SRC)
	@echo $(OBJ)
