### **Wrapping Up: Makefiles Stage**

#### **Overview**
At this stage, we’ve built a solid foundation for understanding and working with Makefiles. While Makefiles are a powerful tool for managing builds, they can become increasingly complex as projects grow. This note summarizes what we’ve covered so far, highlights the limitations of Makefiles, and outlines why transitioning to more advanced tools like CMake might make sense for larger projects.

---

### **What We’ve Covered**

#### **1. Basic Structure of Makefiles**
- **Targets**: Defined what to build (e.g., executables or object files).
  - Example:
    ```make
    all: todo_app todo_tests
    ```
- **Dependencies**: Specified which files a target depends on.
  - Example:
    ```make
    main.o: src/main.cpp src/ui.h src/todo.h
    ```
- **Commands**: Defined how to build the target using compiler commands.
  - Example:
    ```make
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
    ```

#### **2. Variables for Reusability**
- Used variables like `CXX`, `CXXFLAGS`, and `INCLUDES` to make the Makefile more flexible and easier to maintain.
  - Example:
    ```make
    CXX = g++
    CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17 -g
    INCLUDES = -Iexternal/googletest/googletest/include -Iexternal/googletest/googletest -I$(SRC_DIR)
    ```

#### **3. Building Multiple Targets**
- Created separate targets for:
  1. The main application (`todo_app`).
  2. The test executable (`todo_tests`).
- Ensured that each target had its own set of dependencies and build rules.

#### **4. Dependency Management**
- Ensured that files were recompiled only when necessary by specifying dependencies between source files (`.cpp`) and headers (`.h`).

#### **5. Integration with External Libraries**
- Integrated Google Test into the project by:
  1. Cloning it as a Git submodule.
  2. Adding include paths and compilation rules for Google Test in the Makefile.
  3. Linking the test executable with Google Test libraries.

#### **6. Clean Rule**
- Added a `clean` rule to remove generated files, ensuring a clean build environment.
  ```make
  clean:
      rm -f *.o todo_app todo_tests
  ```

#### **7. Compiler Flags**
- Explored common compiler flags like:
  - `-Wall`, `-Wextra`, `-Wpedantic`: Enable warnings to catch potential issues early.
  - `-std=c++17`: Specify the C++ standard.
  - `-pthread`: Enable threading support (required by Google Test).

---

### **What We’ve Built**

1. **CLI To-Do Application**:
   - A simple command-line application organized into production code (`src/`) and tests (`tests/`).

2. **Makefile**:
   - A functional Makefile that builds both the application and test executable.
   - Handles dependencies between source files, headers, and external libraries.

3. **Google Test Integration**:
   - Successfully integrated Google Test as a Git submodule.
   - Configured the Makefile to compile and link Google Test with the test executable.

---

### **Shortcomings of Makefiles**

While Makefiles are powerful for small projects, they have limitations as projects grow in complexity:

#### **1. Manual Dependency Management**
- Dependencies must be manually specified in the Makefile (e.g., listing all headers that a `.cpp` file depends on).
- Forgetting to update dependencies can lead to incorrect builds.

#### **2. Lack of Cross-Platform Support**
- Makefiles are primarily designed for Unix-like systems (Linux/macOS). Building on other platforms (e.g., Windows) requires additional tools or significant modifications.

#### **3. Scalability Issues**
- As projects grow, maintaining a single Makefile becomes cumbersome:
  - Adding new modules or libraries requires updating multiple sections of the file.
  - Conditional builds (e.g., Debug vs Release) add further complexity.

#### **4. No Built-in Dependency Fetching**
- Managing external libraries (like Google Test) requires manual steps (e.g., cloning as a submodule). Tools like CMake simplify this process with built-in support for fetching dependencies.

#### **5. No Automatic Dependency Tracking**
- While our Makefile handles basic dependencies, it doesn’t automatically track all changes (e.g., indirect header file changes). Advanced tools like CMake handle this more effectively.

---

### **What We’ve Learned**

By working with Makefiles, you now have a strong understanding of:
1. How compilers work at a fundamental level (compiling source files into object files, linking them into executables).
2. The structure of a Makefile and how to define targets, dependencies, and commands.
3. Using variables to make the Makefile reusable and maintainable.
4. Handling multiple targets (e.g., building both production code and tests).
5. Integrating external libraries into your project using include paths and linking.
6. The importance of clean builds (`make clean`) and incremental builds (rebuilding only what has changed).

This knowledge provides an excellent foundation for understanding build systems in general.

---

### **Why Transitioning to CMake Makes Sense**

As your project grows or if you want to adopt more advanced features, transitioning to CMake is a logical next step:

#### Key Benefits of CMake:
1. **Cross-Platform Support**:
   - Generates platform-specific build files (e.g., Makefiles on Linux/macOS, Visual Studio projects on Windows).

2. **Automatic Dependency Tracking**:
   - Tracks all dependencies automatically without requiring manual updates.

3. **Out-of-Source Builds**:
   - Keeps build artifacts separate from source code, making it easier to manage large projects.

4. **Built-in Support for External Libraries**:
   - Fetches and manages external libraries like Google Test directly during configuration.

5. **Configurable Build Types**:
   - Easily switch between Debug and Release builds using flags like `cmake .. -DCMAKE_BUILD_TYPE=Debug`.

6. **Integration with IDEs**:
   - Works seamlessly with popular IDEs like CLion, Visual Studio, and VSCode.

7. **LSP Support**:
   - Automatically generates `compile_commands.json` for LSP servers like `clangd`.

---

### Summary

#### What We’ve Achieved with Makefiles:
1. Built a functional CLI To-Do application with production code and tests.
2. Integrated Google Test as an external dependency using Git submodules.
3. Created a robust Makefile that handles multiple targets, dependencies, and compiler flags.

#### Shortcomings of Makefiles:
1. Manual dependency management becomes tedious as projects grow.
2. Limited cross-platform support without significant modifications.
3. Lack of advanced features like automatic dependency tracking or fetching external libraries.
