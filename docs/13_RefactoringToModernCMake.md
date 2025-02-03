------------------------------------------------------------

## Refactoring Our C++ Project with Modern CMake

### Overview

We have reorganized our project so that it is easier to maintain, build, and scale as you learn more about C++ and its build tools. Our new folder structure consists of three main directories:

- **apps:** Contains the executable code (for example, the file with `main()`).
- **libs:** Holds all the core library code (the reusable parts like functions and classes in files such as `todo.cpp` and `ui.cpp`).
- **tests:** Contains all test code (using Google Test, for example).

At the top level, we have one main CMakeLists.txt file that sets up the project and then calls the CMakeLists.txt files in each of these subfolders. We also have a folder for external dependencies (like Google Test) managed as a Git submodule.

### Why Multiple CMake Files?

- **Modularity and Clarity:**  
  Instead of one large file that handles everything, each directory has its own CMakeLists.txt. This divides the project by concerns, making it easier for beginners to see and understand what happens for each part of the project.
  
- **Target-Based Settings:**  
  In modern CMake, we configure settings for individual targets (executables or libraries). That way, when we build our application or run our tests, only the relevant settings and include paths are applied. For example, the apps CMake file links the app with the library (using target_link_libraries), while the tests file tells the compiler where to find header files (using target_include_directories).

### The Multifolder Structure: apps, libs, and tests

- **apps Folder:**  
  Contains the file with the `main()` function and any other code specific to the final executable. Its CMakeLists.txt simply creates the executable and links it with our library.
  
- **libs Folder:**  
  Contains the core library code (implementation files and headers). We create a library target here (for instance, by calling `add_library(todo_lib ...)`). This library is compiled once and then shared with both the app and test targets.
  
- **tests Folder:**  
  Contains test files that include headers from the library. The tests CMakeLists.txt not only compiles the test executable but also links it with the library. It also specifies where to find the headers (so the compiler can locate them) using target_include_directories.

### How CMake Files Call Each Other

- The **top-level CMakeLists.txt** acts as a “table of contents” for the project. It sets common settings like the C++ standard (C++17 in our case) and then uses `add_subdirectory()` to include the CMakeLists.txt files in the **apps**, **libs**, and **tests** folders.
  
- Each subfolder’s CMakeLists.txt defines its own target(s). For example:
  - In **libs/CMakeLists.txt**, we define a library target (todo_lib).
  - In **apps/CMakeLists.txt**, we create an executable (todo_app) and link it with todo_lib.
  - In **tests/CMakeLists.txt**, we create a test executable (todo_tests) and link it with todo_lib and Google Test (using target_link_libraries and target_include_directories).

### Modern Best Practices We Follow

- **Target-Based Configuration:**  
  Instead of using commands that affect the global project (like include_directories), we use target-specific commands such as target_include_directories and target_link_libraries. This makes sure that each target only gets the settings it needs.

- **Separation of Concerns:**  
  With our three-folder structure, we ensure that the code for the executable, core functionality, and tests are separated. This not only helps in keeping things tidy but also encourages reuse: the library code (in libs) is shared between the application and tests.

- **Easier Maintenance and Scalability:**  
  By having a clear folder structure and separating build configurations, it becomes much easier to add new features, executables, or tests without cluttering a single file with hundreds of lines of code.

- **Improved Dependency Management:**  
  Linking the app and tests to the same library target ensures that you do not duplicate your library code across different parts of the project. It also lets you control where the compiler should look for header files, precisely telling it where to find the declarations and implementations it needs.

### Answers to Common Questions (in Simple Terms)

1. **Why use target_include_directories?**  
   This command tells the compiler exactly where to look for header files when building a specific target. For example, when building tests, we use it to point the compiler to the directory where our library headers are located.

2. **Why do we list source files for the app but not for tests?**  
   The executable (todo_app) needs to know which source files to compile, so we list them. In contrast, the tests may only need to include headers (to access classes and functions) and then link to the already compiled library (todo_lib). Thus, we don’t duplicate the library source file listings in the tests.

3. **Are tests using the compiled library or directly the source files?**  
   Both the app and tests use the compiled library. In tests, we add an extra include directory (using target_include_directories) so that the test code can find the header files. Then we link the tests to the compiled library (todo_lib) so they run the same code as the app.

### In Conclusion

This refactoring and reorganization help us transition from an old Makefile-based build to a modern, modular CMake-based build. The benefits include:
  
- **Improved readability and maintainability:** Clear separation through multiple CMakeLists.txt files and a well-organized directory structure.
- **Scalable design:** As your project grows, it’s easy to add more targets (like additional executables or tests) without cluttering your build configuration.
- **Modern practices:** Using target-based settings, separating apps, libs, and tests, and linking targets correctly all lead to fewer build issues and a more robust codebase.

This approach is ideal for anyone learning C++ and its build tools—it breaks down the process into smaller, understandable pieces while preparing you for larger, real-world projects.
