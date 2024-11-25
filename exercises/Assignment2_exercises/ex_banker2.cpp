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
int available_current_value[3] = {-1, -1, -1};
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
            available_current_value[0] = number1;
            available_current_value[1] = number2;
            available_current_value[2] = number3;
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

void initializeAvailable() {
    for (int i = 0; i < COLUMN; i++) {
        available[0][i] = available_current_value[i];
    }
}

void assignCurrentAvailable(int process_number) {
    for (int i = 0; i < COLUMN; i++) {
        available[process_number][i] = available_current_value[i];
    }
}

void initializeProcess() {
    for (int i = 0; i < ROW; i++) {
        process_queue.push(i);
    }
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

    resources.A += available_current_value[0];
    resources.B += available_current_value[1];
    resources.C += available_current_value[2];
    
    cout << "Total Resources:  " << resources.A << " "
                      << resources.B << " "
                      << resources.C << "\n"
                      << endl;
}

void printQueue(queue<int> process_executed) {
    cout << "PROCESSES IN QUEUE: ";

    while(!process_executed.empty()) {
        cout << "P"<< process_executed.front() << " ";
        process_executed.pop();
    }
    cout << endl;
}

void printTable() {
    /*
    int counter = 0;
    while (counter >= 1) {
    
        counter++;
    }*/
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
}

// ========== ========== ========== ========== ========== //

bool isExecutable(int process_counter) {  // (available > need)
    for (int i = 0; i < COLUMN; i++) {
        if (available_current_value[i] > need[process_counter][i]) {
            return true;
        }
    }
    return false;
}

void executeProcess(int process_number) {

    assignCurrentAvailable(process_number);

    for (int i = 0; i < COLUMN; i++) {
        available[process_number][i]
        = (allocation[process_number][i] + available[process_number][i]);
        
        available_current_value[i] = available[process_number][i];
        allocation[process_number][i] = 0;
    }

    // Remove element in queue
}

void removeElementInQueue(int executing_process, queue<int>& process_queue) {
    /* 
    Reference:
    https://www.geeksforgeeks.org/how-to-remove-a-specific-element-from-queue/
    */

    queue<int> reference_queue;
    int queue_size = process_queue.size();
    int counter = 0;

    while (process_queue.front() != executing_process
        && !process_queue.empty()) {
        
        reference_queue.push(process_queue.front());
        process_queue.pop();
        counter++;
    }

    // Element is found
    if (!process_queue.empty()) {
        executing_process = process_queue.front();
        // cout << "Executing P" << executing_process << endl;
        process_queue.pop();

        while (!reference_queue.empty()) {
            process_queue.push(reference_queue.front());
            reference_queue.pop();
        }

        int replaceIndex = (queue_size - counter - 1);
        while (replaceIndex--) {
            int process = process_queue.front();
            process_queue.pop();
            process_queue.push(process);
        }
    }
    cout << endl;
}

void buildBankersAlgorithm() {

    int process_number = 0;
    // = process_queue.size();
    // cout << "Process Number: " << process_number << endl;

    int process_counter = 0;
    while (!process_queue.empty() /*process_counter != 5*/) {
        
        if (isExecutable(process_counter) == true) {
            cout << "TRUE" << endl;

            // delete 1 in process counter

            executeProcess(process_number); // pop & print
            printTable();

            removeElementInQueue(process_number, process_queue);
            cout << "Executing P" << process_number << endl;
            cout << "\n"; printQueue(process_queue);

            process_counter = 0;
            // process_number++;
            cout << "Counter: " << process_counter << endl;
            cout << "P number:" << process_number << endl;
            // available += allocation[][]
        }
        else if (isExecutable(process_counter) == false) {
            cout << "FALSE" << endl;
            cout << "P" << process_counter << endl;
            process_counter++;
            process_number++;
            cout << "Counter: " << process_counter << endl;
            cout << "P number:" << process_number;

            //process_number = process_counter;
        }
        cout << "\n======== ======== ======== ======== ========\n" << endl;
    }
}



/*
int writeOutputFile() {
    ofstream outputFile("output.txt");
}
*/

int main() {

    readInputFile();
    initializeAvailable();
    initializeProcess();
    calculateNeed();
    
    cout << "===== ===== Initial Value from a Table ===== =====" << endl;
    printTable();
    cout << "\n"; printQueue(process_queue);

    // cout << "\n===== ===== ===== Running ===== ===== =====" << endl;
    // buildBankersAlgorithm();


    return 0;

}