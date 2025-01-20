### **Note: Organizing Code and Adding Google Test**

#### **Starting Point**
We began by reorganizing the project structure to improve maintainability and scalability. Initially, all source files (`.cpp` and `.h`) were located in the root directory. We moved them into a dedicated `src/` folder, updated the Makefile to reflect this change, and then proceeded to integrate Google Test for testing.

---

### **Step 1: Reorganizing Code**

#### **New Project Structure**
The source files were moved into a `src/` folder, resulting in the following structure:

```
project/
├── src/                # Application source files
│   ├── main.cpp
│   ├── ui.cpp
│   ├── ui.h
│   ├── todo.cpp
│   ├── todo.h
├── Makefile            # Build rules in root directory
```

#### **Updated Makefile**
The Makefile was updated to account for the new location of the source files. Specifically:
1. Added a variable for the `src/` directory (`SRC_DIR`).
2. Updated file paths for `.cpp` and `.h` files.
3. Ensured object files (`*.o`) are still created in the root directory.

**Updated Makefile:**
```make
# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17 -g

# Directory for source files
SRC_DIR = src

# Application sources and objects
APP_SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/ui.cpp $(SRC_DIR)/todo.cpp
APP_OBJS = main.o ui.o todo.o

# Target executable name
APP_TARGET = todo_app

# Default rule: build the application
all: $(APP_TARGET)

# Rule to build the application executable
$(APP_TARGET): $(APP_OBJS)
	$(CXX) $(APP_OBJS) -o $(APP_TARGET)

# Rules for compiling source files into object files
main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/ui.h $(SRC_DIR)/todo.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o main.o

ui.o: $(SRC_DIR)/ui.cpp $(SRC_DIR)/ui.h $(SRC_DIR)/todo.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/ui.cpp -o ui.o

todo.o: $(SRC_DIR)/todo.cpp $(SRC_DIR)/todo.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/todo.cpp -o todo.o

# Clean rule to remove generated files
clean:
	rm -f *.o $(APP_TARGET)
```

#### **Build Workflow**
1. Run `make` to build the application:
   ```bash
   make
   ```
2. Run `make clean` to remove generated files:
   ```bash
   make clean
   ```

This reorganization improves code clarity and prepares the project for further enhancements, such as adding tests.

---

### **Step 2: Adding Google Test**

After organizing the code, we added **Google Test** as a local dependency for testing.

#### **Updated Project Structure**
We introduced two new folders:
- **`tests/`**: For test code.
- **`external/`**: For external libraries (Google Test).

The updated structure:
```
project/
├── src/                # Application source files
│   ├── main.cpp
│   ├── ui.cpp
│   ├── ui.h
│   ├── todo.cpp
│   ├── todo.h
├── tests/              # Test source files
│   ├── simple_test.cpp # Simple test file for verification
├── external/           # External libraries (Google Test)
│   └── googletest/     # Cloned Google Test repository
├── Makefile            # Build rules for app and tests
```

#### **Cloning Google Test**
We cloned Google Test into the `external/` folder:
```bash
git clone https://github.com/google/googletest.git external/googletest
```

This ensures that Google Test is part of the project and does not rely on system-wide installation.

---

### **Step 3: Writing a Simple Test**

We created a simple test file `tests/simple_test.cpp` to verify that Google Test is working correctly:

**File: `tests/simple_test.cpp`:**
```cpp
#include <gtest/gtest.h>

TEST(SimpleTest, BasicAssertions) {
    // Expect equality: 2 + 2 = 4
    EXPECT_EQ(2 + 2, 4);

    // Expect inequality: 5 != 3
    EXPECT_NE(5, 3);
}
```

This test includes Google Test (`<gtest/gtest.h>`) and defines one test case (`SimpleTest`) with two assertions:
- `EXPECT_EQ`: Checks if two values are equal.
- `EXPECT_NE`: Checks if two values are not equal.

---

### **Step 4: Updating the Makefile**

#### Key Changes in the Makefile:
To build both the application and test executable, we updated the Makefile to:
1. Compile Google Test from its source files.
2. Build a test executable (`todo_tests`) that links with Google Test.
3. Handle dependencies between application code, test code, and Google Test.

**Updated Makefile Sections**:

1. **Google Test Compilation**:
   - Compiles Google Test’s core functionality (`gtest-all.cc`) and its default `main()` function (`gtest_main.cc`) into object files:
     ```make
     GTEST_SRC = $(EXTERNAL_DIR)/googletest/src/gtest-all.cc
     GTEST_MAIN_SRC = $(EXTERNAL_DIR)/googletest/src/gtest_main.cc

     gtest-all.o: $(GTEST_SRC)
         $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

     gtest-main.o: $(GTEST_MAIN_SRC)
         $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
     ```

2. **Include Paths**:
   - Added include paths for Google Test headers and application headers:
     ```make
     INCLUDES = -I$(EXTERNAL_DIR)/googletest/include -I$(EXTERNAL_DIR)/googletest -I$(SRC_DIR)
     ```

3. **Test Target**:
   - Added a target for building the test executable by linking:
     - The compiled Google Test object files (`gtest-all.o`, `gtest-main.o`).
     - The compiled test file (`simple_test.o`).
     ```make
     TEST_TARGET = todo_tests

     $(TEST_TARGET): gtest-all.o gtest-main.o simple_test.o
         $(CXX) gtest-all.o gtest-main.o simple_test.o -pthread -o $@
     ```

4. **Test File Compilation**:
   ```make
   simple_test.o: tests/simple_test.cpp
       $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
   ```

5. **Default Rule**:
   The default rule now builds both the application executable (`todo_app`) and test executable (`todo_tests`):
   ```make
   all: $(APP_TARGET) $(TEST_TARGET)
   ```

6. **Clean Rule**:
   Removes all generated files (object files and executables):
   ```make
   clean:
       rm -f *.o $(APP_TARGET) $(TEST_TARGET)
   ```

---

### **Compilation Workflow**

1. Build everything (application + tests):
   ```bash
   make
   ```

2. Run the application:
   ```bash
   ./todo_app
   ```

3. Run the tests:
   ```bash
   ./todo_tests
   ```

---

### **What We Had to Compile and Why**

1. **Google Test Core Library (`gtest-all.o`)**:
   Contains all core functionality of Google Test (e.g., assertions like `EXPECT_EQ`, `EXPECT_NE`).

2. **Google Test Main Function (`gtest-main.o`)**:
   Provides a default `main()` function that initializes Google Test and runs all defined tests.

3. **Test File (`simple_test.o`)**:
   Contains our custom test cases (e.g., assertions for basic math).

4. **Application Code (`main.o`, `ui.o`, `todo.o`)**:
   Compiled into an executable (`todo_app`) for running the main application.

5. **Linking**:
   For tests, we linked `gtest-all.o`, `gtest-main.o`, and `simple_test.o` into a single executable (`todo_tests`) using threading support (`-pthread`).

---

### Verification

After running `./todo_tests`, you should see output like this:

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from SimpleTest
[ RUN      ] SimpleTest.BasicAssertions
[       OK ] SimpleTest.BasicAssertions (0 ms)
[----------] 1 test from SimpleTest (0 ms total)

[----------] Global test environment tear-down.
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
```

This confirms that Google Test is integrated correctly!

---

### Summary of Changes

1. Reorganized code into a dedicated `src/` folder.
2. Cloned Google Test into an `external/` folder.
3. Wrote a simple test in `tests/simple_test.cpp`.
4. Updated the Makefile to compile both application code and tests.

This setup provides a strong foundation for adding more tests and features in the future! Let me know if you’d like further clarification or enhancements!
