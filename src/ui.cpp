#include "ui.h"

#include <iostream>
#include <string>

void displayMenu() {
  std::cout << "To-Do List Manager\n";
  std::cout << "1. Add Task\n";
  std::cout << "2. View Tasks\n";
  std::cout << "3. Delete Task\n";
  std::cout << "4. Exit\n";
  std::cout << "Enter your choice: ";
}

void runApplication(TodoManager& todoManager) {
  int choice;

  while (true) {
    displayMenu();
    std::cin >> choice;

    switch (choice) {
      case 1: {
        std::cin.ignore();  // Clear input buffer
        std::cout << "Enter task: ";
        std::string task;
        std::getline(std::cin, task);
        todoManager.addTask(task);
        std::cout << "Task added!\n";
        break;
      }
      case 2: {
        const auto& tasks = todoManager.getTasks();
        if (tasks.empty()) {
          std::cout << "No tasks available.\n";
        } else {
          std::cout << "Your Tasks:\n";
          for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i] << "\n";
          }
        }
        break;
      }
      case 3: {
        const auto& tasks = todoManager.getTasks();
        if (tasks.empty()) {
          std::cout << "No tasks to delete.\n";
        } else {
          std::cout << "Your Tasks:\n";
          for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". " << tasks[i] << "\n";
          }
          std::cout << "Enter task number to delete: ";
          size_t index;
          std::cin >> index;
          if (index > 0 && index <= tasks.size()) {
            todoManager.deleteTask(index - 1);
            std::cout << "Task deleted!\n";
          } else {
            std::cout << "Invalid task number.\n";
          }
        }
        break;
      }
      case 4:
        std::cout << "Goodbye!\n";
        return;
      default:
        std::cout << "Invalid choice. Try again.\n";
    }
    std::cout << "\n";  // Add some spacing for readability
  }
}
