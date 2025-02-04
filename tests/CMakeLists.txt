# tests/CMakeLists.txt

# Build the test executable from the test source file
add_executable(todo_tests simple_test.cpp)

# Let the compiler know where to find the library headers (from libs/)
target_include_directories(todo_tests PRIVATE ${PROJECT_SOURCE_DIR}/libs)

# Link against the library (todo_lib) and GoogleTest
target_link_libraries(todo_tests PRIVATE todo_lib GTest::gtest_main)

target_compile_options(todo_tests PRIVATE -Wall -Wextra -Wpedantic)
# Enable testing and register this test with CTest
enable_testing()
add_test(NAME SimpleTest COMMAND todo_tests)

