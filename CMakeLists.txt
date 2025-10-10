# CMakeLists.txt for paperkey project
# This file configures the build process for the paperkey application using CMake.

# Require CMake version 3.10 or higher
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(paperkey)

# Set C standard to C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add compiler flags for warnings and pedantic mode (equivalent to original Makefile)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -W -pedantic")

# Include directories for headers
# Current directory for config.h and other local headers
include_directories(.)
# gl/ directory for gnulib headers
include_directories(gl)

# Check for getopt functions
include(CheckFunctionExists)
check_function_exists(getopt HAVE_GETOPT)
check_function_exists(getopt_long HAVE_GETOPT_LONG)
check_function_exists(getopt_long_only HAVE_GETOPT_LONG_ONLY)

# List of source files for the paperkey executable
set(SOURCES
    paperkey.c
    extract.c
    restore.c
    parse.c
    packets.c
    output.c
    stream.c
    gl/sha1.c
    gl/unistd.c
)

# Conditionally add getopt sources if not available on system
if(NOT HAVE_GETOPT_LONG)
    list(APPEND SOURCES gl/getopt.c)
endif()
if(NOT HAVE_GETOPT_LONG_ONLY)
    list(APPEND SOURCES gl/getopt1.c)
endif()

# Create the paperkey executable from the source files
add_executable(paperkey ${SOURCES})

# Note: No external libraries are linked as per the original Makefile analysis.
# If additional libraries are needed in the future, add them here using target_link_libraries().