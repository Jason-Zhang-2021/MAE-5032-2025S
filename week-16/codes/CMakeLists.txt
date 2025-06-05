cmake_minimum_required(VERSION 3.10)
project(petsc_hdf5_demo C)

if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

# ----------------------------
# Handle PETSc + HDF5 loading
# ----------------------------
set(PETSC_DIR /Users/juliu/lib/petsc-3.22.2-debug)
set(PETSC_ARCH .)
set(HDF5_ROOT /Users/juliu/lib/hdf5-1.14.2)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

find_package(HDF5 REQUIRED)

set(ENV{PKG_CONFIG_PATH} ${PETSC_DIR}/lib/pkgconfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(PETSC REQUIRED IMPORTED_TARGET PETSc)

# ----------------------------
# Compiler flags & output dirs
# ----------------------------
set(CMAKE_C_COMPILER ${PETSC_DIR}/bin/mpicc)
set(CMAKE_C_STANDARD 99)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type." FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ----------------------------
# Add the executable
# ----------------------------
add_executable( demo demo-hdf5-petsc.c)

# ----------------------------
# Include and link libraries
# ----------------------------
target_include_directories( demo PRIVATE
  ${HDF5_INCLUDE_DIRS}
  ${PETSC_INCLUDE_DIRS}
)

target_link_libraries( demo
  ${HDF5_LIBRARIES}
  ${PETSC_LIBRARIES}
)

# EOF
