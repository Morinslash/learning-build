#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

void displayMenu() {
  cout << "To-Do List Manager\n";
  cout << "1. Add Task\n";
  cout << "2. View Task\n";
  cout << "3. Delete Task\n";
  cout << "4. Exit\n";
  cout << "Enter your choice: \n";
}

void addTask(vector<string>& tasks) {
  cout << "Entter task: ";
  string task;
  std::cin.ignore();
  std::getline(std::cin, task);
  tasks.push_back(task);
  cout << "Task added!\n";
}

void viewTasks(const vector<string>& tasks) {
  if (tasks.empty()) {
    cout << "No tasks avaialbe.\n";
    return;
  }
  cout << "Your tasks:\n";
  for (size_t i = 0; i < tasks.size(); ++i) {
    cout << i + 1 << ". " << tasks[i] << "\n";
  }
}

void deleteTask(vector<string>& tasks) {
  if (tasks.empty()) {
    cout << "Not tasks to delete.\n";
    return;
  }
  viewTasks(tasks);
  cout << "Enter tasks number to delete: ";
  size_t index;
  std::cin >> index;
  if (index == 0 || index > tasks.size()) {
    cout << "Invalid task number.\n";
    return;
  }
  tasks.erase(tasks.begin() + index - 1);
  cout << "Task delete!\n";
}

int main() {
  vector<string> tasks;
  int choice;

  while (true) {
    displayMenu();
    std::cin >> choice;

    switch (choice) {
      case 1:
        addTask(tasks);
        break;
      case 2:
        viewTasks(tasks);
        break;
      case 3:
        deleteTask(tasks);
      break;
      case 4:
        cout << "Googbye!\n";
        return 0;
      default:
        cout << "Invalid choice. Try again.\n";
    }
    cout << "\n";
  }
}
