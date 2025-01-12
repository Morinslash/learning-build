#ifndef TODO_H
#define TODO_H

#include <vector>
#include <string>

// Class to manage to-do list functionality
class TodoManager {
public:
    void addTask(const std::string& task);          // Add a new task
    const std::vector<std::string>& getTasks() const; // Get all tasks
    void deleteTask(size_t index);                 // Delete a task by index

private:
    std::vector<std::string> tasks; // Internal storage for tasks
};

#endif // TODO_H
