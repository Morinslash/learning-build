### **Note: Transitioning from Makefiles to CMake**

#### **Overview**
We have successfully transitioned our project from using a **Makefile** to **CMake**. This change simplifies the build process, integrates better with external libraries like Google Test, and prepares the project for scalability and cross-platform compatibility.

This note explains what we’ve done, compares key parts of the Makefile to their equivalents in CMake, and highlights the benefits of this transition.

---

### **What We’ve Done**

1. Replaced the Makefile with a `CMakeLists.txt` file.
2. Configured CMake to:
   - Build the application executable (`todo_app`) from `src/`.
   - Build the test executable (`todo_tests`) from `tests/`, linking it with Google Test.
3. Used Google Test as a Git submodule and integrated it into the CMake build system using `add_subdirectory()`.
4. Leveraged CMake’s built-in testing functionality with `enable_testing()` and `add_test()`.
5. Ensured that both executables are built with the same compiler settings and dependencies.

---

### **Matching Parts: Makefile vs CMake**

#### **1. Compiler and Flags**
In the Makefile, we explicitly defined the compiler and flags:
```make
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17 -g
```

In CMake, we specify the compiler standard directly:
```cmake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```

CMake automatically applies appropriate warning flags based on your compiler.

---

#### **2. Source Files**
In the Makefile, we listed source files manually:
```make
APP_SRC = src/main.cpp src/ui.cpp src/todo.cpp
APP_OBJS = main.o ui.o todo.o
```

In CMake, we use a variable to list source files:
```cmake
set(SRC_FILES
    src/main.cpp
    src/ui.cpp
    src/todo.cpp
)
```

This makes it easy to reuse the same list for multiple targets or configurations.

---

#### **3. Application Executable**
In the Makefile, we defined a target for building `todo_app`:
```make
todo_app: $(APP_OBJS)
	$(CXX) $(APP_OBJS) -o todo_app
```

In CMake, this is done using `add_executable()`:
```cmake
add_executable(todo_app ${SRC_FILES})
```

CMake automatically handles object file generation and linking.

---

#### **4. Test Executable**
In the Makefile, we manually linked Google Test libraries to build `todo_tests`:
```make
todo_tests: gtest-all.o gtest-main.o simple_test.o
	$(CXX) gtest-all.o gtest-main.o simple_test.o -pthread -o todo_tests
```

In CMake, we use Google Test’s predefined targets (`GTest::gtest_main`) for simplicity:
```cmake
add_executable(todo_tests tests/simple_test.cpp)
target_link_libraries(todo_tests PRIVATE GTest::gtest_main)
```

This eliminates the need to manually manage Google Test source files or threading support.

---

#### **5. Include Paths**
In the Makefile, we specified include paths manually:
```make
INCLUDES = -Iexternal/googletest/googletest/include -Iexternal/googletest/googletest -Isrc
```

In CMake, we use `include_directories()`:
```cmake
include_directories(
    src
)
```

This ensures that application headers are accessible during compilation. We don't have to specify GoogleTest as it will be added using other command.

---

#### **6. Google Test Integration**
In the Makefile, we compiled Google Test source files (`gtest-all.cc`, `gtest_main.cc`) manually:
```make
gtest-all.o: external/googletest/googletest/src/gtest-all.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

gtest-main.o: external/googletest/googletest/src/gtest_main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
```

In CMake, we simply add Google Test as a subdirectory and link its predefined targets:
```cmake
add_subdirectory(external/googletest)
target_link_libraries(todo_tests PRIVATE GTest::gtest_main)
```

This approach is more robust and eliminates manual management of Google Test’s internals.

---

#### **7. Testing Support**
The Makefile didn’t include any built-in support for running tests.

In CMake, we enable testing with:
```cmake
enable_testing()
add_test(NAME TodoTests COMMAND todo_tests)
```

This integrates your tests with CMake’s testing framework (CTest), allowing you to run tests using:
```bash
ctest
```

---

#### **8. Clean Rule**
The Makefile included a `clean` rule to remove generated files:
```make
clean:
	rm -f *.o todo_app todo_tests
```

With CMake, you don’t need a manual clean rule. Simply run:
```bash
rm -rf build/
```
This removes all build artifacts since they are stored in the `build/` directory (out-of-source builds).

---

### **Benefits of Transitioning to CMake**

1. **Simplified Build Process**:
   - No need to manually manage object files or dependencies.
   - Automatically tracks changes in source files and rebuilds only what’s necessary.

2. **Better Dependency Management**:
   - Easily integrates external libraries like Google Test using `add_subdirectory()` or other mechanisms (e.g., FetchContent).

3. **Cross-Platform Compatibility**:
   - Generates platform-specific build files (e.g., Makefiles on Linux/macOS, Visual Studio projects on Windows).

4. **Out-of-Source Builds**:
   - Keeps build artifacts separate from source code, making your project directory cleaner.

5. **Built-in Testing Support**:
   - Integrates with CTest for running and managing tests.

6. **LSP Support**:
   - Automatically generates `compile_commands.json` for better integration with tools like Neovim’s LSP or VSCode.

---

### Summary

#### What We’ve Done:
1. Replaced the Makefile with a `CMakeLists.txt` file.
2. Configured CMake to build both application and test executables.
3. Integrated Google Test as a Git submodule using `add_subdirectory()`.
4. Leveraged predefined targets (`GTest::gtest_main`) for simpler test integration.
5. Enabled testing support with `enable_testing()` and `add_test()`.

#### Key Benefits of Using CMake Over Makefiles:
1. Simplifies dependency management.
2. Provides cross-platform compatibility.
3. Automatically tracks dependencies between source files.
4. Supports out-of-source builds for cleaner project structure.
5. Integrates seamlessly with modern development tools (e.g., LSPs).
