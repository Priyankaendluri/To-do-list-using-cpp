#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const string FILENAME = "tasks.txt";

void loadTasks(vector<string>& tasks) {
    ifstream file(FILENAME);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            if (!line.empty())
                tasks.push_back(line);
        }
        file.close();
    }
}

void saveTasks(const vector<string>& tasks) {
    ofstream file(FILENAME);
    for (const auto& task : tasks) {
        file << task << endl;
    }
    file.close();
}

void showTasks(const vector<string>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks yet!\n";
        return;
    }
    cout << "\n----- Your To-Do List -----\n";
    for (size_t i = 0; i < tasks.size(); i++) {
        cout << (i + 1) << ". " << tasks[i] << endl;
    }
    cout << "----------------------------\n";
}

void showMenu() {
    cout << "\n1. View tasks\n2. Add task\n3. Remove task\n4. Exit\nChoose an option: ";
}

int main() {
    vector<string> tasks;
    loadTasks(tasks);

    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // clear newline from buffer

        switch (choice) {
            case 1:
                showTasks(tasks);
                break;

            case 2: {
                string newTask;
                cout << "Enter new task: ";
                getline(cin, newTask);
                tasks.push_back(newTask);
                saveTasks(tasks);
                cout << "Task added!\n";
                break;
            }

            case 3: {
                showTasks(tasks);
                if (!tasks.empty()) {
                    int index;
                    cout << "Enter task number to remove: ";
                    cin >> index;
                    if (index >= 1 && index <= (int)tasks.size()) {
                        tasks.erase(tasks.begin() + (index - 1));
                        saveTasks(tasks);
                        cout << "Task removed!\n";
                    } else {
                        cout << "Invalid task number.\n";
                    }
                }
                break;
            }

            case 4:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}