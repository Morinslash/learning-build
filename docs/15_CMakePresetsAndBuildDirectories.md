## Using CMakePresets to Manage Build Configurations and Build Directories

### Overview

Modern CMake lets you separate configuration settings (like compiler flags, build types, generator choices, and more) from your standard CMakeLists.txt files by using external preset files. This helps you easily switch between Debug and Release builds (or other configurations) without manually passing flags each time. It also allows you to keep a clean and maintainable build system.

### What Are CMakePresets?

- **CMakePresets.json** is an external JSON file placed at your project's root (or even in a subdirectory if needed) that specifies project-wide configuration details.
- Using presets, you can define:
  - The generator to use (for example, "Unix Makefiles" if you aren’t using Ninja).
  - The build type (set via `CMAKE_BUILD_TYPE` for single-config generators or using multi-config generators’ options).
  - The binary directory (the folder where the build output will be generated).
  - Other cache variables like debugging symbols or optimization settings.

This means you can run something like:
  `cmake --preset debug`
and have your build directory configured with Debug settings—without manually setting flags every time.

### How to Specify Different Build Directories

If you want your Debug and Release builds to be output in separate folders (for example, build/debug and build/release), you can do that in your preset file. One common approach is to use a placeholder variable such as `${presetName}` in the `binaryDir` field.

For example:
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
      "binaryDir": "${sourceDir}/build/${presetName}",
      "cacheVariables": {
        "CMAKE_EXPORT_COMPILE_COMMANDS": "ON",
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
In this example:
- The base preset named “default” sets the generator to “Unix Makefiles” and chooses a binary folder pattern using `${sourceDir}/build/${presetName}`.
- The `debug` preset overrides the build type to Debug.
- The `release` preset uses the Release build type.
- When you run `cmake --preset debug`, CMake will create or use the directory `build/debug` (because `${presetName}` is replaced by the current preset name). Similarly, `cmake --preset release` will use `build/release`.

### Why Are We Using Multiple CMakeLists.txt Files and a Preset File?

- **Modular Structure:**  
  Our project is organized into folders (apps, libs, tests). Each one has its own CMakeLists.txt, which means configuration is localized. For example, the library in libs/ handles its own compiler warnings and include directories; the executable in apps/ links against the library; and tests under tests/ link to both the library and any testing frameworks.
  
- **Target-Based Configuration:**  
  We add compiler warning flags with commands like `target_compile_options()` so that each target is built with recommended settings. This avoids global options that might affect targets unpredictably.

- **Separation of Build Settings from Project Structure:**  
  The top-level CMakeLists.txt works as the “table of contents” by adding subdirectories. It sets common project properties such as the C++ standard. Configuration that is specific to Debug versus Release (or any other build type) is then off-loaded to the CMakePresets.json file.

- **Ease of Switching Build Configurations:**  
  With the presets, you don’t need to continuously remember to pass flags like `-DCMAKE_BUILD_TYPE=Debug`. Instead, you simply configure your build directory with a preset (for example, debug or release). You can also easily have separate build directories per configuration (debug: build/debug, release: build/release), which is especially helpful when using single-config generators.

### Running Build

After this change to build our projet we have to specify the directory in the `build` folder we want to build like this

```
cmake --build build/debug
```

### Summary

- **CMakePresets.json** centralizes your configuration. It specifies settings like the generator, build type, and even where the build outputs go via `binaryDir`.  
- In a preset file, you can use variable substitution (e.g., `${presetName}`) so that different build types are output in their own folders (build/debug vs. build/release).
- Modifying your build configuration is as simple as invoking:
  `cmake --preset debug`  
to configure your build directory for Debug mode, then running:
  `cmake --build build`
- Our project structure—with separate CMakeLists.txt files for apps, libs, and tests—follows best practices for modularity, clearer target configuration, and maintainability.
