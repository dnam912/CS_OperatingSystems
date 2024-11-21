#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int available[3] = {-1, -1, -1};
int allocation[5][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};
int maximum[5][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};
int need[5][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};

vector<int> process_queue;

void print_table() {
    cout << "Available: " << available[0] << " " 
        << available[1] << " " << available[2] << endl;
    cout << "Allocation - Maximum - Need" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "P" << (i) << ":  ";
        for (int j = 0; j < 3; j++) {
            cout << allocation[i][j] << " ";
        }
        cout << "- ";
        for (int k = 0; k < 3; k++) {
            cout << maximum[i][k] << " ";
        }
        cout << "  - ";
        for (int k = 0; k < 3; k++) {
            cout << need[i][k] << " ";
        }
        cout << endl;
    }
}

int read_file() {

    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Error - File cannot be opened" << endl;
        return -1;
    } 

    int line_number = -1;
    string line;
    while (getline(file, line)) {
        int number1, number2, number3, number4, number5, number6;
        istringstream iss(line);
        iss >> number1 >> number2 >> number3 >> number4 >> number5 >> number6;

        if (line_number == -1) {
            available[0] = number1;
            available[1] = number2;
            available[2] = number3;
        } else {
            allocation[line_number][0] = number1;
            allocation[line_number][1] = number2;
            allocation[line_number][2] = number3;
            maximum[line_number][0] = number4;
            maximum[line_number][1] = number5;
            maximum[line_number][2] = number6;
        }

        // cout << number1 << "-" << number2 << "-" << number3 << endl;
        line_number++;
    }

    file.close();
    return 0;
}

void calculate_need() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

void initialize_process_queue() {
    for (int i = 0; i < 5; i++) {
        // If process is in queue, it is not executed.
        process_queue.push_back(i); 
    }
}

void execute_process(int process_number) {

    cout << "Executing: P" << process_number << endl;

    for (int i = 0; i < 3; i++) {
        available[i] = allocation[process_number][i] + available[i];
        allocation[process_number][i] = 0;
    }

    process_queue.erase(
        remove(process_queue.begin(), process_queue.end(), process_number), 
        process_queue.end()
    );
}

bool is_executable_process(int process_number) {
    for (int i = 0; i < 3; i++) {
        if (available[i] < need[process_number][i]) {
            return false;
        }
    }
    return true;
}

void banker_algorithm() {

    int repetition = -1;

    while (process_queue.size() != 0) {

        repetition = process_queue.size();
        
        for (int i = 0; i < process_queue.size(); i++) {
            int process_number = process_queue[i];
            if (is_executable_process(process_number) == true) {
                execute_process(process_number);
                break;
            }
        }

        if (repetition == process_queue.size()) {
            break;
        }
    }

    if (process_queue.size() == 0) {
        cout << "THE SYSTEM IS SAFE!" << endl;
    } else {
        cout << "THE SYSTEM IS NOT SAFE!" << endl;
    }

}

int main() {

    read_file();
    calculate_need();
    initialize_process_queue();
    banker_algorithm();

    return 0;
}