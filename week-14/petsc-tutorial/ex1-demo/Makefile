
# -*- mode: makefile -*-
PETSC_DIR := /Users/juliu/lib/petsc-3.22.2-debug
PETSC_ARCH := .

# This sample (GNU) Makefile can be used to compile PETSc applications with a single
# source file and can be easily modified to compile multi-file applications.
# It relies on pkg_config tool, and PETSC_DIR and PETSC_ARCH variables.
# Copy this file to your source directory as "Makefile" and modify as needed.
#
# For example - a single source file can be compiled with:
#
#  $ cd src/snes/tutorials/
#  $ make -f $PETSC_DIR/share/petsc/Makefile.user ex17
#
# The following variable must either be a path to petsc.pc or just "petsc" if petsc.pc
# has been installed to a system location or can be found in PKG_CONFIG_PATH.

# Additional libraries that support pkg-config can be added to the list of PACKAGES below.

PETSC_PC := $(PETSC_DIR)/$(PETSC_ARCH)/lib/pkgconfig/petsc.pc
CFLAGS := $(shell pkg-config --cflags $(PETSC_PC))
LDFLAGS := $(shell pkg-config --libs-only-L --libs-only-other $(PETSC_PC))
LDLIBS := $(shell pkg-config --libs-only-l $(PETSC_PC)) -lm

# Files
EXEC := ex1.out
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

#Rules
$(EXEC) : $(OBJ)
	$(LINK.cc) $(LDLIBS) -o $@ $^
	$(RM) $(OBJ)
%.o : %.c 
	$(COMPILE.c) $(OUTPUT_OPTION) $<

.PHONY : clean
clean :
	$(RM) $(EXEC) $(OBJ)
