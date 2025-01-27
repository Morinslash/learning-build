# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(CPP_Build_Learning)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable compile_commands.json generation for LSP support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add source files for the application
set(SRC_FILES
    src/main.cpp
    src/ui.cpp
    src/todo.cpp
)

# Include directories for application headers
include_directories(src)

# Add the application executable (todo_app)
add_executable(todo_app ${SRC_FILES})

# Add the test executable (todo_tests)
add_executable(todo_tests tests/simple_test.cpp)

# Add Google Test subdirectory (from Git submodule)
add_subdirectory(external/googletest)

# Link Google Test libraries to the test executable
target_link_libraries(todo_tests PRIVATE GTest::gtest_main)

# Enable testing support in CMake
enable_testing()

# Register the test executable for CTest
add_test(NAME SimpleTest COMMAND todo_tests)
