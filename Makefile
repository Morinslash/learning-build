
# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17 -g

# Directories
SRC_DIR = src
TEST_DIR = tests
EXTERNAL_DIR = external/googletest

# Application sources and objects
APP_SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/ui.cpp $(SRC_DIR)/todo.cpp
APP_OBJS = main.o ui.o todo.o

# Test sources and objects
TEST_SRC = $(TEST_DIR)/simple_test.cpp
TEST_OBJS = simple_test.o

# Target names
APP_TARGET = todo_app
TEST_TARGET = todo_tests

# Google Test sources and objects (compiled locally)
GTEST_SRC = $(EXTERNAL_DIR)/googletest/src/gtest-all.cc
GTEST_MAIN_SRC = $(EXTERNAL_DIR)/googletest/src/gtest_main.cc
GTEST_OBJS = gtest-all.o gtest-main.o

# Include directories for headers (Google Test + src/)
INCLUDES = -I$(EXTERNAL_DIR)/googletest/include -I$(EXTERNAL_DIR)/googletest -I$(SRC_DIR)

# Default rule: build both app and tests
all: $(APP_TARGET) $(TEST_TARGET)

# Rule to build the application executable
$(APP_TARGET): $(APP_OBJS)
	$(CXX) $(APP_OBJS) -o $(APP_TARGET)

# Rule to build the test executable (links with Google Test)
$(TEST_TARGET): $(GTEST_OBJS) $(TEST_OBJS)
	$(CXX) $(GTEST_OBJS) $(TEST_OBJS) -pthread -o $(TEST_TARGET)

# Rules for compiling application source files into object files
main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/ui.h $(SRC_DIR)/todo.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o main.o

ui.o: $(SRC_DIR)/ui.cpp $(SRC_DIR)/ui.h $(SRC_DIR)/todo.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/ui.cpp -o ui.o

todo.o: $(SRC_DIR)/todo.cpp $(SRC_DIR)/todo.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/todo.cpp -o todo.o

# Rule to compile simple_test.cpp into an object file
simple_test.o: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile gtest-all.cc into an object file (Google Test core library)
gtest-all.o: $(GTEST_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile gtest_main.cc into an object file (Google Test main function)
gtest-main.o: $(GTEST_MAIN_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f *.o $(APP_TARGET) $(TEST_TARGET)
