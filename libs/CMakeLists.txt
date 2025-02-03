# libs/CMakeLists.txt

# List your library source files
set(SRC_FILES
    todo.cpp
    ui.cpp
)

# Create a library target named "todo_lib"
add_library(todo_lib ${SRC_FILES})

# Specify include directories for this library target; any files that include headers from libs/
# will be able to find them here.
target_include_directories(todo_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
