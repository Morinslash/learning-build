# apps/CMakeLists.txt

# Build the executable from main.cpp (now in the apps folder)
add_executable(todo_app main.cpp)

# Link the todo_lib library so that the executable finds the implementations from libs/
target_link_libraries(todo_app PRIVATE todo_lib)

target_compile_options(todo_app PRIVATE -Wall -Wextra -Wpedantic)
