cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Create CMake project
set(PROJECT "regulator_regulate")
project(${PROJECT} VERSION 1.0.0 LANGUAGES C ASM)

# Set Language Standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set names of needed components
set(LIBRARY_CORE "${PROJECT}_lib-core")

set(TARGET ${PROJECT})

# Add libararies
add_subdirectory("../../core" ${CMAKE_CURRENT_BINARY_DIR}/core)

# Add files for the build process
set(SOURCES
        "main.c"
)

# Create and configure target
add_executable(${TARGET}
        ${SOURCES}
)
target_link_libraries(${TARGET}
        ${LIBRARY_CORE}
)