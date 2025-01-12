#### **Refactor Overview**
We refactored our single-file To-Do List program into a modular structure with three distinct parts:
1. **`main.cpp`**: Acts as the entry point, bootstrapping the application and orchestrating interactions between modules.
2. **User Interface (`ui.h` and `ui.cpp`)**: Handles all user interactions (e.g., displaying menus, collecting input/output). It is decoupled from the internal logic of managing tasks.
3. **To-Do Module (`todo.h` and `todo.cpp`)**: Manages task-related functionality (e.g., adding, deleting, storing tasks). It encapsulates its internal data structure and provides a clean interface.

This modular design improves code organization, separation of concerns, reusability, and scalability.

---

### **Compiling All Files at Once**
For small projects, you can compile all `.cpp` files in a single command:

```bash
g++ main.cpp ui.cpp todo.cpp -o todo
```

#### **What Happens in This Command**
1. The compiler processes each `.cpp` file:
   - Preprocesses and compiles `main.cpp`, `ui.cpp`, and `todo.cpp` into object files internally.
   - Example: `main.o`, `ui.o`, `todo.o`.
2. The linker combines these object files into a single executable (`todo`).

This approach is simple and works well for small projects where all files are recompiled every time.

---

### **Limitations of Compiling All Files at Once**
1. **Inefficiency in Large Projects**:
   - If only one file changes (e.g., `ui.cpp`), this approach recompiles *all* files unnecessarily, even those that haven’t changed.
   - This wastes time as the project grows larger.

2. **No Reuse of Object Files**:
   - By compiling everything in one step, you lose the ability to reuse previously compiled object files (`.o`), which could speed up incremental builds.

3. **Complexity with Flags**:
   - Managing multiple flags for each file becomes cumbersome as the project grows.

---

### **Compiling to Object Files**
To address these limitations, you can compile each `.cpp` file into an object file (`.o`) separately and then link them:

#### **Commands for Separate Compilation**
1. Compile each source file into an object file:
   ```bash
   g++ -c main.cpp -o main.o
   g++ -c ui.cpp -o ui.o
   g++ -c todo.cpp -o todo.o
   ```
   - The `-c` flag tells the compiler to stop after generating the object file (no linking yet).
   - Each `.o` file contains machine code for its corresponding `.cpp` file.

2. Link all object files into a single executable:
   ```bash
   g++ main.o ui.o todo.o -o todo
   ```

#### **Advantages of Separate Compilation**
1. **Incremental Builds**:
   - If only one file changes (e.g., `ui.cpp`), you only need to recompile that file:
     ```bash
     g++ -c ui.cpp -o ui.o
     ```
     Then relink all object files:
     ```bash
     g++ main.o ui.o todo.o -o todo
     ```

2. **Reusability**:
   - Object files can be reused across builds or shared between projects if their code doesn’t change.

3. **Improved Efficiency**:
   - Only changed files are recompiled, reducing build times for large projects.

---

### **Best Practice Command with Recommended Flags**
For best practices, you should use compiler flags to enable warnings, debugging information (if needed), or optimizations:

#### Example Command to Compile All Files at Once with Flags
```bash
g++ main.cpp ui.cpp todo.cpp -Wall -Wextra -Wpedantic -Werror -std=c++17 -g -o todo
```

#### Example Commands for Separate Compilation with Flags
1. Compile each file with recommended flags:
   ```bash
   g++ -c main.cpp -Wall -Wextra -Wpedantic -Werror -std=c++17 -g -o main.o
   g++ -c ui.cpp -Wall -Wextra -Wpedantic -Werror -std=c++17 -g -o ui.o
   g++ -c todo.cpp -Wall -Wextra -Wpedantic -Werror -std=c++17 -g -o todo.o
   ```
2. Link the object files into an executable:
   ```bash
   g++ main.o ui.o todo.o -o todo
   ```

---

### **Why This Approach Becomes Unmanageable**
While separate compilation is efficient, managing multiple commands manually becomes tedious as the project grows:
- You must remember which files have changed and recompile them individually.
- You must repeatedly type out long commands with multiple flags.
- Forgetting a flag or recompiling the wrong file can lead to errors or inconsistencies.

---

### **Introducing Build Tools (Makefiles)**
To solve these issues, tools like **Make** automate the build process by:
1. Tracking dependencies between source files and object files.
2. Automatically recompiling only the necessary files when changes are detected.
3. Simplifying commands by defining rules in a `Makefile`.

For example, instead of typing multiple commands manually, you could simply run:
```bash
make
```
The tool will handle everything—compilation, linking, flags—based on rules defined in your `Makefile`.

---

### Summary of Compilation Workflow

| Approach                          | Pros                                         | Cons                                      |
|-----------------------------------|---------------------------------------------|------------------------------------------|
| Compile All Files at Once         | Simple for small projects                   | Inefficient for incremental builds       |
| Separate Compilation (Object Files) | Efficient for large projects; reusable objects | Tedious to manage manually               |
| Use Build Tools (Make)            | Automates compilation; tracks dependencies  | Requires learning Makefile syntax        |

---

