#include "ui.h"
#include "todo.h"

int main() {
    TodoManager todoManager; // Encapsulates task management
    runApplication(todoManager); // Start the app via UI
    return 0;
}
