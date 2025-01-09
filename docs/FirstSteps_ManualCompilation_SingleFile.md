### Summary Note: Building and Running a Simple C++ To-Do List Manager

#### **Project Overview**
We have created a simple **CLI To-Do List Manager** in C++ with the following functionality:
1. **Add Task**: Allows the user to input a task and store it in memory.
2. **View Tasks**: Displays all tasks stored in memory.
3. **Delete Task**: Removes a specific task by its index.
4. **Exit**: Ends the program.

The program uses basic **C++ Standard Library** components, such as:
- `iostream`: For input/output operations (e.g., `std::cin`, `std::cout`).
- `vector`: To store tasks dynamically in a list-like structure.
- `string`: To handle text input for tasks.

#### **Why No External Libraries?**
The program relies solely on the **C++ Standard Library**, which is included with every C++ compiler. This means:
- We don’t need to download or link any external libraries.
- Standard headers like `<iostream>`, `<vector>`, and `<string>` are automatically found by the compiler because they are part of the compiler's standard library implementation.

This simplicity allows us to focus on learning how to compile and run the program without worrying about external dependencies.

---

#### **Build System Explanation**
Currently, we are using the most basic build system: manually invoking the compiler (`g++`) from the command line. Here's what happens during this process:

1. **Compilation**:
   - The source code (`todo.cpp`) is translated into an object file (`todo.o`), which contains machine code but is not yet executable.
   - The compiler checks for syntax errors, resolves references to included headers (like `<iostream>`), and generates intermediate code.

2. **Linking**:
   - The object file is linked with other necessary components, such as the C++ Standard Library and system libraries, to produce a final executable (`todo`).
   - The linker ensures that all function calls (e.g., `std::cout`) are resolved to their actual implementations in the libraries.

When we run:
```bash
g++ -o todo todo.cpp
```
The `g++` command performs both compilation and linking in one step:
- `-o todo`: Specifies the name of the output executable (`todo`).
- `todo.cpp`: The input source file.

---

#### **Understanding Compilation and Linking**

Here’s a breakdown of what happens under the hood:

1. **Preprocessing**:
   - The preprocessor handles directives like `#include`. For example, when we include `<iostream>`, it replaces it with the actual contents of the header file, which defines input/output functions like `std::cout`.

2. **Compilation**:
   - After preprocessing, the compiler translates the human-readable C++ code into machine-readable assembly code.
   - This assembly code is then converted into an object file (`.o`), which contains machine instructions but lacks references to external functions (e.g., `std::cout`).

3. **Linking**:
   - The linker combines our object file with other necessary libraries (e.g., C++ Standard Library) to create a complete, runnable program.
   - It resolves symbols (function names, variables) used in our code by finding their definitions in linked libraries.

For example:
- When we use `std::cout`, its implementation resides in the C++ Standard Library. During linking, this implementation is connected to our program.

---

#### **Why Is This Process Important?**
Understanding compilation and linking helps us:
1. Debug build issues (e.g., missing libraries or unresolved symbols).
2. Optimize builds by separating compilation and linking steps (useful for larger projects).
3. Transition to more advanced build systems like Make or CMake later on.
