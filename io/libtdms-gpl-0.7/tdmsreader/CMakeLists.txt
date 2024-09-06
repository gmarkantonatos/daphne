cmake_minimum_required(VERSION 3.10)
project(my_project)

# Add the path to the tdms library and include directories
set(TDMS_DIR /home/gerasmark/daphne/io/libtdms-gpl-0.7/build/lib)  # Path to the compiled tdms library
set(TDMS_INCLUDE_DIR /home/gerasmark/daphne/io/libtdms-gpl-0.7/include)  # Path to tdms header files

# Include the tdms header files
include_directories(${TDMS_INCLUDE_DIR})

# Define the executable for your project
add_executable(my_program main.cpp)

# Link the tdms library
target_link_libraries(my_program ${TDMS_DIR}/libtdms.a)
