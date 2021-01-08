cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Create CMake project
set(PROJECT "pid-regulator")
project(${PROJECT} VERSION 1.0.0)

# Add libararies
add_subdirectory("tests/regulate")
add_subdirectory("tests/autotune")
