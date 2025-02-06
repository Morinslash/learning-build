#include "todo.h"

void TodoManager::addTask(const std::string &task) { tasks.push_back(task); }

const std::vector<std::string> &TodoManager::getTasks() const { return tasks; }

void TodoManager::deleteTask(size_t index) {
  if (index < tasks.size()) {
    tasks.erase(tasks.begin() + index);
  }
}
