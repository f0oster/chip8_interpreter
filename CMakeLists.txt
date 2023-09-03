cmake_minimum_required(VERSION 3.10)

# Set your project name
project(chip8_interpreter)

# Specify the required C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


# Collect all source files into a variable
file(GLOB SOURCES "src/*.c")

# Include header files directory
include_directories(include)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# If you have any libraries to link against, use the target_link_libraries() function
# target_link_libraries(${PROJECT_NAME})