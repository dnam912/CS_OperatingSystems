#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int ROW = 5;
int COLUMN = 3;

int allocation[5][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};
int maximum[5][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};
int avail_initial_value[3] = {-1, -1, -1};
int available[5][3] =  {{-1,-1,-1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
int need[5][3] = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}};

queue<int> process_queue;


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
            avail_initial_value[0] = number1;
            avail_initial_value[1] = number2;
            avail_initial_value[2] = number3;
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

void calculateNeed() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// ========== ========== ========== ========== ========== //

void initializeProcess() {
    for (int i = 0; i < ROW; i++) {
        process_queue.push(i);
    }
}

void printQueue(queue<int> process) {
    while(!process.empty()) {
        cout << "P"<< process.front() << endl;
        process.pop();
    }
    cout << endl;
}

// ========== ========== ========== ========== ========== //

void buildBankersAlgorithm() {
    /*
    if (available > need) {
        executeProcess() // pop & print
        proces_counter = 0;
        available += allocation[][]
    } else {
        process_counter++;
    }
    */
}

// ========== ========== ========== ========== ========== //

void printInitialAvailable() {
    cout << "Initial Available: ";
    for (int i = 0; i < COLUMN; i++) {
        available[0][i] = avail_initial_value[i];
        cout << avail_initial_value[i] << " ";
    }
    cout << endl;
}

struct ABC {int A = 0; int B = 0; int C = 0;};
void printTotalResources() {
    // ALLOCATION + AVAILABLE
    ABC resources;
    for (int i = 0; i < ROW; i++) {
        resources.A += allocation[i][0];
        resources.B += allocation[i][1];
        resources.C += allocation[i][2];
    }

    resources.A += avail_initial_value[0];
    resources.B += avail_initial_value[1];
    resources.C += avail_initial_value[2];
    
    cout << "Total Resources:  " << resources.A << " "
                      << resources.B << " "
                      << resources.C << "\n"
                      << endl;
}

void printTable() {
    printInitialAvailable();
    printTotalResources();

    // ROW
    cout << "Allocation - Maximum - Available - Need" << endl;
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
        
        cout << " -   ";
        for (int m = 0; m < COLUMN; m++) {
            cout << available[i][m] << " ";
        }

        cout << "  - ";
        for (int n = 0; n < COLUMN; n++) {
            cout << need[i][n] << " ";
        }

        cout << endl;
    }
    cout << endl;

}



/*
int writeOutputFile() {
    ofstream outputFile("output.txt");
}
*/



int main() {

    readInputFile();
    initializeProcess();
    calculateNeed();
    
    printTable();
    printQueue(process_queue);

    return 0;

}