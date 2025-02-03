cmake_minimum_required(VERSION 3.10)

project(CPP_Build_Learning LANGUAGES CXX)

# Set projectwide properties.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include the subdirectories for libraries, executable, tests, and external dependencies.
add_subdirectory(libs)
add_subdirectory(apps)
add_subdirectory(tests)
add_subdirectory(external/googletest)
