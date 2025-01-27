### **Note: Simplifying CMake Workflow with Command Options and Shell Scripts**

#### **Overview**
When working with CMake, the default workflow often requires navigating into a `build/` directory to configure, build, and run your project. While this is clean and keeps build artifacts separate from source files, it can feel cumbersome to switch directories repeatedly. 

This note explains how to streamline your workflow by:
1. Using CMake's `-S` (source) and `-B` (build) options to run commands from the root of your project.
2. Automating common tasks like configuring, building, and testing with a simple shell script.

---

### **1. Basic Commands for CMake Workflow**

CMake provides options to specify the source and build directories, allowing you to run all commands from the root of your project while keeping build artifacts in the `build/` folder.

#### **Key Commands**

1. **Configure the Build**:
   ```bash
   cmake -S . -B build
   ```
   - `-S .`: Specifies the source directory (the current directory).
   - `-B build`: Specifies the build directory (`build/`).
   - This command generates the necessary build files (e.g., Makefiles) in the `build/` folder.

2. **Build the Project**:
   ```bash
   cmake --build build
   ```
   - This command invokes the appropriate build system (e.g., Makefiles) in the `build/` folder to compile your project.

3. **Run Tests**:
   ```bash
   ctest --test-dir build
   ```
   - Runs tests using CTest, which is integrated with CMake.
   - `--test-dir build`: Specifies the directory where test executables are located.

4. **Clean the Build**:
   If you need to clean up all generated files, simply delete the `build/` folder:
   ```bash
   rm -rf build/
   ```

---

### **2. Why Use a Shell Script?**

While these commands are simple, running them repeatedly can become tedious as your project grows or if you frequently switch between building and testing. A shell script automates these tasks, making your workflow faster and more efficient.

#### **Benefits of Using a Shell Script**
1. **Convenience**:
   - Instead of typing multiple commands every time, you can run a single script.
2. **Consistency**:
   - Ensures that all team members use the same configuration and build steps.
3. **Flexibility**:
   - You can extend the script to handle additional tasks (e.g., cleaning builds, switching between Debug and Release configurations).

---

### **3. Example Shell Script**

Here’s an example script (`build.sh`) that automates common tasks like configuring, building, and testing:

#### File: `build.sh`
```bash
#!/bin/bash

# Define the build directory
BUILD_DIR="build"

# Handle the "clean" argument first to avoid unnecessary steps
if [ "$1" == "clean" ]; then
    rm -rf $BUILD_DIR
    echo "Build directory cleaned."
    exit 0
fi

# Create the build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

# Run CMake configuration
cmake -S . -B $BUILD_DIR

# Build the project
cmake --build $BUILD_DIR

# Optionally run tests if "test" argument is provided
if [ "$1" == "test" ]; then
    ctest --test-dir $BUILD_DIR
fi
```

---

### **4. How to Use the Script**

1. Save this script as `build.sh` in your project root.
2. Make it executable:
   ```bash
   chmod +x build.sh
   ```

3. Run common tasks with a single command:

#### Configure and Build:
```bash
./build.sh
```

#### Configure, Build, and Run Tests:
```bash
./build.sh test
```

#### Clean Build Directory:
```bash
./build.sh clean
```

---

### **5. Why This Workflow is Useful**

#### Without a Script:
You would need to manually type commands like these every time:
```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build  # To run tests (optional)
rm -rf build/           # To clean builds (optional)
```

#### With a Script:
You can achieve all of this with simpler commands like:
```bash
./build.sh         # Configure and Build
./build.sh test    # Configure, Build, and Test
./build.sh clean   # Clean Builds
```

This not only saves time but also ensures consistency across builds.

---

### Summary

#### Basic Commands for CMake Workflow:
1. Configure: `cmake -S . -B build`
2. Build: `cmake --build build`
3. Test: `ctest --test-dir build`
4. Clean: `rm -rf build/`

#### Why Use a Shell Script?
- Automates repetitive tasks.
- Simplifies workflow by consolidating multiple commands into one.
- Ensures consistency across builds.

By combining CMake’s flexibility with a simple shell script, you can streamline your development process while keeping your project organized and efficient.

Let me know if you’d like further clarification or enhancements!
