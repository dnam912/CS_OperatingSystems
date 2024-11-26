#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <algorithm>

using namespace std;

int ROW = 5;
int COLUMN = 3;

int available[3] = {-1, -1, -1};
int allocation[5][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};
int maximum[5][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};
int need[5][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};

vector<int> process_queue;


int readInputFile() {
    ifstream input("input.txt");
    if (!input.is_open()) {
        cerr << "ERROR: File cannot be opened" << endl;
        return -1;
    }

    int row_number = -1;
    string row;
    while (getline(input, row)) {
        int number1, number2, number3, number4, number5, number6;
        istringstream iss(row);
        iss >> number1 >> number2 >> number3 >> number4 >> number5 >> number6;

        if (row_number == -1) {
            available[0] = number1;
            available[1] = number2;
            available[2] = number3;
        } else {
            allocation[row_number][0] = number1;
            allocation[row_number][1] = number2;
            allocation[row_number][2] = number3;
            maximum[row_number][0] = number4;
            maximum[row_number][1] = number5;
            maximum[row_number][2] = number6;
        }
        
        row_number++;
    }

    input.close();
    return 0;
}

// ========== ========== ========== ========== ========== //

void calculateNeed() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

void initializeProcessQueue() {
    for (int i = 0; i < ROW; i++) {
        // If process is in queue, it is not executed.
        process_queue.push_back(i); 

        cout << "P" << i << " ";
    } cout << endl;
}

bool isExecutable(int process_number) {  // (available > need)
    for (int i = 0; i < COLUMN; i++) {
        if (available[i] > need[process_number][i]) {
            return true;
        }
    }
    return false;
}



void executeProcess(int process_number) {

    cout << "Executing: P" << process_number << endl;

    for (int i = 0; i < COLUMN; i++) {
        available[i] = allocation[process_number][i] + available[i];
        allocation[process_number][i] = 0;
    }

    // Completely remove a specific element in vector
    process_queue.erase(
        remove(process_queue.begin(), process_queue.end(), process_number), 
        process_queue.end()
    );
}
/**/

void banker_algorithm() {

    int repetition = -1;

    while (process_queue.size() != 0) {

        repetition = process_queue.size();
        
        for (int i = 0; i < process_queue.size(); i++) {
            int process_number = process_queue[i];
            if (isExecutable(process_number) == true) {
                executeProcess(process_number);
                break;
            }
        }

        // No more process is left in queue
        if (repetition == process_queue.size()) {
            break;
        }
    }

    //

}


// ========== ========== ========== ========== ========== //

struct ABC {int A = 0; int B = 0; int C = 0;};
void printTotalResources() {
    // ALLOCATION + AVAILABLE
    ABC resources;
    for (int i = 0; i < ROW; i++) {
        resources.A += allocation[i][0];
        resources.B += allocation[i][1];
        resources.C += allocation[i][2];
    }

    resources.A += available[0];
    resources.B += available[1];
    resources.C += available[2];
    
    cout << "Total Resources: " << resources.A << " "
                      << resources.B << " "
                      << resources.C << "\n";
}

void printTable() {
    printTotalResources();


    cout << "Available: ";
    for (int i = 0; i < COLUMN; i++) {
        cout << available[i] << " ";
    }
    cout << endl;

    // ROW
    cout << "Allocation - Maximum - Need" << endl;
    for (int i = 0; i < ROW; i++) {

        cout << "P" << i << ":  ";

        // COLUMN
        for (int j = 0; j < COLUMN; j++) {
            cout << allocation[i][j] << " ";
        }

        cout << "-  ";
        for (int k = 0; k < COLUMN; k++) {
            cout << maximum[i][k] << " ";
        }

        cout << "  - ";
        for (int n = 0; n < COLUMN; n++) {
            cout << need[i][n] << " ";
        }

        cout << endl;
    }
}



int main() {

    readInputFile();
    calculateNeed();
    printTable();
    initializeProcessQueue();
    banker_algorithm();

    return 0;

}