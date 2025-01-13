# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17 -g

# Target executalbe name
TARGET = todo

# Object files
OBJS = main.o ui.o todo.o

# Default rule (builds the executalbe)
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
