# Compiler
CXX = g++
CXXFLAGS = -O3 -std=c++11 -march=native

# OpenBLAS Paths
OPENBLAS_INC = -I/Users/juliu/lib/openblas/include/openblas
OPENBLAS_LIB = -L/Users/juliu/lib/openblas/lib -lopenblas

# Target executable
TARGET = blas_demo

# Source file
SRC = blas_demo.cpp
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

# Compile object file
$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) $(OPENBLAS_INC) -c $< -o $@

# Link final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OPENBLAS_LIB) $^ -o $@

# Clean build files
clean:
	rm -f $(TARGET) $(OBJ)

