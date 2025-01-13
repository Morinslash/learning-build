### **Note: Automating Builds with Makefiles**

#### **Overview**
A Makefile is a configuration file used by the `make` build automation tool to streamline the process of compiling and linking multiple files. It defines **rules** that specify how to build targets (like object files or executables) and their dependencies. Using a Makefile ensures efficient, consistent, and automated builds, especially for larger projects.

---

### **Structure of a Makefile**
A Makefile consists of:
1. **Targets**: The name of what you want to build (e.g., an executable or an object file).
2. **Dependencies**: Files required to build the target (e.g., `.cpp` or `.h` files).
3. **Commands**: The actions to execute to create the target (e.g., `g++` commands).

#### Basic Syntax:
```make
target: dependencies
    command
```
- The `target` is what you’re building.
- The `dependencies` are the files needed to build the target.
- The `command` is what runs to create the target.

---

### **Example Makefile for To-Do List Project**

Here’s a Makefile for our modular To-Do List project:

```make
# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17 -g

# Target executable name
TARGET = todo

# Object files
OBJS = main.o ui.o todo.o

# Default rule (builds the executable)
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile main.cpp into main.o
main.o: main.cpp ui.h todo.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Rule to compile ui.cpp into ui.o
ui.o: ui.cpp ui.h todo.h
	$(CXX) $(CXXFLAGS) -c ui.cpp -o ui.o

# Rule to compile todo.cpp into todo.o
todo.o: todo.cpp todo.h
	$(CXX) $(CXXFLAGS) -c todo.cpp -o todo.o

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)
```

---

### **How It Works**

#### **1. Default Rule**
The default rule is the first rule in the Makefile:
```make
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)
```
- This rule builds the final executable (`todo`) by linking all object files (`main.o`, `ui.o`, `todo.o`).
- The target (`$(TARGET)`) depends on the object files (`$(OBJS)`).
- The command (`$(CXX) $(OBJS) -o $(TARGET)`) links all object files into the executable.

#### **2. Rules for Object Files**
Each object file has its own rule:
```make
main.o: main.cpp ui.h todo.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

ui.o: ui.cpp ui.h todo.h
	$(CXX) $(CXXFLAGS) -c ui.cpp -o ui.o

todo.o: todo.cpp todo.h
	$(CXX) $(CXXFLAGS) -c todo.cpp -o todo.o
```
- These rules specify how each `.cpp` file is compiled into its corresponding `.o` file.
- The dependencies ensure that if a `.cpp` or `.h` file changes, only the affected object file is recompiled.
- Each rule follows the same pattern as the default rule:
  - Target (`main.o`, `ui.o`, etc.).
  - Dependencies (`main.cpp`, `ui.h`, etc.).
  - Command (`g++` with flags).

#### **3. Clean Rule**
The `clean` rule removes all generated files:
```make
clean:
	rm -f $(OBJS) $(TARGET)
```
- This is useful for starting fresh or cleaning up temporary files.
- Run it with:
  ```bash
  make clean
  ```

---

### **Order of Evaluation in a Makefile**

1. **First Rule is Default**:
   - By default, `make` starts with the first rule in the file. In this case, it’s:
     ```make
     $(TARGET): $(OBJS)
     ```
   - This tells `make` to build the executable (`todo`) by ensuring all object files (`main.o`, `ui.o`, `todo.o`) are up-to-date.

2. **Dependency Resolution**:
   - If any dependencies (e.g., `main.o`) are missing or out-of-date, `make` evaluates their respective rules (e.g., how to build `main.o`).

3. **Order of Execution**:
   - The order of rules in the Makefile doesn’t matter beyond the first/default rule.
   - Dependencies determine which rules are executed and in what order.

For example:
- If only `ui.cpp` changes, `make` will:
  1. Recompile `ui.cpp` into `ui.o`.
  2. Relink all object files into `todo`.

---

### **Compilation Workflow**

#### Single Command Using Makefile:
To build your project, simply run:
```bash
make
```

#### What Happens Internally:
1. `make` starts with the default rule (`$(TARGET): $(OBJS)`).
2. It checks whether each dependency (`main.o`, `ui.o`, `todo.o`) exists and is up-to-date.
3. For outdated or missing dependencies, it evaluates their respective rules (e.g., how to build `main.o`).
4. Once all object files are up-to-date, it links them into the final executable.

---

### **Benefits of Using a Makefile**

1. **Automation**:
   - Simplifies builds—no need to type long commands manually.
   - Automatically tracks which files need recompiling based on changes.

2. **Efficiency**:
   - Only recompiles changed files, saving time on large projects.

3. **Consistency**:
   - Ensures all files are compiled with the same flags and settings.

4. **Clean Builds**:
   - The `clean` rule allows you to remove generated files easily.

---

### **Best Practice Command with Flags**
If you were building manually without a Makefile, you would need to type something like this:

```bash
g++ main.cpp ui.cpp todo.cpp -Wall -Wextra -Wpedantic -Werror -std=c++17 -g -o todo
```

Or for separate compilation:

```bash
g++ -c main.cpp -Wall -Wextra -Wpedantic -Werror -std=c++17 -g -o main.o
g++ -c ui.cpp -Wall -Wextra -Wpedantic -Werror -std=c++17 -g -o ui.o
g++ -c todo.cpp -Wall -Wextra -Wpedantic -Werror -std=c++17 -g -o todo.o
g++ main.o ui.o todo.o -o todo
```

While this is doable for small projects, it becomes unmanageable as projects grow larger or require frequent changes.

---

### **Why Use a Makefile?**
A Makefile solves these problems by automating the process:
1. Tracks dependencies between source files and object files.
2. Automatically recompiles only what’s necessary.
3. Consolidates commands and flags into one place for consistency and simplicity.

With a Makefile, building your project becomes as simple as running:
```bash
make
```

And cleaning up temporary files is just as easy:
```bash
make clean
```

