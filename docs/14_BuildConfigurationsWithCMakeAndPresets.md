## Build Configurations with CMake and CMakePresets

### Overview

Modern CMake allows us to separate configuration and build instructions using a modular structure. Our project is organized into three main folders:
- **apps:** Contains executable code (e.g., main.cpp).
- **libs:** Contains the reusable library code (e.g., todo.cpp, ui.cpp, and their corresponding headers).
- **tests:** Contains test files (e.g., simple_test.cpp) that verify the behavior of our library and executable.

Each folder has its own CMakeLists.txt file that defines targets (a library, an executable, or tests) and sets target-specific build options. The top-level CMakeLists.txt simply includes these subdirectories, keeping the overall configuration clean and modular.

### Compiler Warning Flags

To improve code quality, we add recommended compiler warning flags such as `-Wall`, `-Wextra`, and `-Wpedantic` in each CMakeLists.txt file using `target_compile_options()`. This ensures every target (library, executable, or tests) is built with the same warning policies.

For example, in our libs/CMakeLists.txt we add:
```cmake
target_compile_options(todo_lib PRIVATE -Wall -Wextra -Wpedantic)
```
This tells CMake to pass these flags when compiling the code for `todo_lib`.

### CMakePresets.json

**Purpose:**  
CMakePresets.json is an external JSON file that lets you predefine build configurations (such as Debug or Release) so that you do not have to manually pass CMake variables (like `CMAKE_BUILD_TYPE`) on the command line each time.

**What It Does:**  
- When you run a command such as `cmake --preset debug`, CMake reads the preset file to configure your build directory in Debug mode. It sets the necessary flags (for instance, enabling debug symbols) and any additional cache variables.
- Then, when you run `cmake --build build`, your project is built using the Debug configuration setup in that build directory.

**Example Preset File (for Makefiles):**
```json
{
  "version": 3,
  "cmakeMinimumRequired": {
    "major": 3,
    "minor": 19,
    "patch": 0
  },
  "configurePresets": [
    {
      "name": "default",
      "hidden": true,
      "generator": "Unix Makefiles",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    },
    {
      "name": "debug",
      "inherits": "default",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug"
      }
    },
    {
      "name": "release",
      "inherits": "default",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    }
  ]
}
```

### Key Points

- **Separating Build Structure:**  
  - The top-level CMakeLists.txt includes subdirectories for apps, libs, and tests.
  - Each subdirectory’s CMakeLists.txt defines its own target(s) and adds target-specific configuration (like include directories and compiler flags).

- **Setting Compiler Flags:**  
  - Warning flags (e.g., `-Wall -Wextra -Wpedantic`) are added via `target_compile_options()` in each CMakeLists.txt.
  - This ensures consistency across all build targets regardless of the build configuration.

- **Using CMakePresets.json:**  
  - This file manages build configurations (Debug, Release, etc.) externally.
  - You configure your build directory with a preset (`cmake --preset debug`), and then simply build with `cmake --build build`.
  - Note that presets work with your build system of choice—if you aren’t using Ninja, you can set the "generator" to "Unix Makefiles" (or another generator that fits your workflow).

- **Flexible Target Building:**  
  - With these tools, you can build individual targets in different configurations. For instance, you can configure your project for Debug and then build only the library target by running:
    ```bash
    cmake --build build --target todo_lib
    ```
  - This builds the library in Debug mode as defined by the preset.

### Conclusion

By adopting these modern practices, our build system becomes much easier to maintain and extend. Compiler warnings are applied consistently to all parts of the project, and CMakePresets.json simplifies switching between different build configurations. This setup is ideal for beginners and helps pave the way to more advanced techniques in managing multi-target, multi-configuration C++ projects.

