#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


int availableResources[3] = {-1, -1, -1};

class Process {
private:

    int processNumber = -1;

    int allocA = -1;
    int maxA = -1;
    int needA = -1;

    int allocB = -1;
    int maxB = -1;
    int needB = -1;
    
    int allocC = -1;
    int maxC = -1;
    int needC = -1;

public:

    Process(int processNumber,
            int allocA, int allocB, int allocC, 
            int maxA, int maxB, int maxC,
            int needA, int needB, int needC) {
        this->processNumber = processNumber;
        
        this->allocA = allocA;
        this->allocB = allocB;
        this->allocC = allocC;

        this->maxA = maxA;
        this->maxB = maxB;
        this->maxC = maxC;

        this->needA = needA;
        this->needB = needB;
        this->needC = needC;
    }

    void setProcessNumber(int processNumber) {
        this->processNumber = processNumber;
    }
    int getProcessNumber() {
        return this->processNumber;
    }

    void setAllocA(int allocA) {
        this->allocA = allocA;
    }
    int getAllocA() {
        return this->allocA;
    }

    void setAllocB(int allocB) {
        this->allocB = allocB;
    }
    int getAllocB() {
        return this->allocB;
    }

    void setAllocC(int allocC) {
        this->allocC = allocC;
    }
    int getAllocC() {
        return this->allocC;
    }

    void setMaxA(int maxA) {
        this->maxA = maxA;
    }
    int getMaxA() {
        return this->maxA;
    }

    void setMaxB(int maxB) {
        this->maxB = maxB;
    }
    int getMaxB() {
        return this->maxB;
    }

    void setMaxC(int maxC) {
        this->maxB = maxC;
    }
    int getMaxC() {
        return this->maxC;
    }

    void setNeedA(int needA) {
        this->needA = needA;
    }
    int getNeedA() {
        return this->needA;
    }

    void setNeedB(int needB) {
        this->needA = needB;
    }
    int getNeedB() {
        return this->needB;
    }

    void setNeedC(int needC) {
        this->needC = needC;
    }
    int getNeedC() {
        return this->needC;
    }
};

vector<Process*> processVector;

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
            availableResources[0] = number1;
            availableResources[1] = number2;
            availableResources[2] = number3;
        } else {
            Process* temp = new Process(row_number,
                number1, number2, number3, 
                number4, number5, number6, 
                number4 - number1, number5 - number2, number6 - number3
                );
            processVector.push_back(temp);
        }
        
        row_number++;
    }

    input.close();
    return 0;
}

// ========== ========== ========== ========== ========== //

void calculateNeed() {
    // for (int i = 0; i < ROW; i++) {
    //     for (int j = 0; j < COLUMN; j++) {
    //         need[i][j] = maximum[i][j] - allocation[i][j];
    //     }
    // }
}


void initializeAvailable() {
    // for (int i = 0; i < COLUMN; i++) {
    //     available[0][i] = available_current_value[i];
    // }
}

void assignCurrentAvailable(int process_number) {
    // for (int i = 0; i < COLUMN; i++) {
    //     available[process_number][i] = available_current_value[i];
    // }
}


// ========== ========== ========== ========== ========== //

struct ABC {int A = 0; int B = 0; int C = 0;};
void printTotalResources() {
    // ALLOCATION + AVAILABLE
    ABC resources;
    // for (int i = 0; i < ROW; i++) {
    //     resources.A += allocation[i][0];
    //     resources.B += allocation[i][1];
    //     resources.C += allocation[i][2];
    // }

    // resources.A += available_current_value[0];
    // resources.B += available_current_value[1];
    // resources.C += available_current_value[2];
    
    // cout << "Total Resources:  " << resources.A << " "
    //                   << resources.B << " "
    //                   << resources.C << "\n"
    //                   << endl;
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
    // printTotalResources();
        counter++;
    }*/

    
    cout << "Process # - Allocation - Maximum - Need" << endl;
    
    for (int i = 0; i < processVector.size(); i++) {

        cout << "Process " << processVector[i]->getProcessNumber() << " | ";
        
        cout << " " << processVector[i]->getAllocA() << " "
             << " " << processVector[i]->getAllocB() << " "
             << " " << processVector[i]->getAllocC();

        cout << "     " << processVector[i]->getMaxA() << " "
             << " " << processVector[i]->getMaxB() << " "
             << " " << processVector[i]->getMaxC();

        cout << "   " << processVector[i]->getNeedA() << " "
             << " " << processVector[i]->getNeedB() << " "
             << " " << processVector[i]->getNeedC();

        cout << endl;
    }
}

// ========== ========== ========== ========== ========== //

bool isExecutable(int processNumber) {  // (available > need)
    // THE DIFFERENCE OF SIMPLE VECTOR AND CLASS VECTOR
    // Impossible to know ProcessNumber in processVector 
    // unless we compare the parameter of processNumber to vector's processNum
    Process* temp;
    for (int i = 0; i < processVector.size(); i++) {
        if (processVector[i]->getProcessNumber() == processNumber) {
            temp = processVector[i];
        }
    }

    if (availableResources[0] < temp->getNeedA()) {
        return false;
    }
    if (availableResources[1] < temp->getNeedB()) {
        return false;
    }
    if (availableResources[2] < temp->getNeedC()) {
        return false;
    }

    return true;
}

void executeProcess(int process_number) {

    assignCurrentAvailable(process_number);

    // for (int i = 0; i < COLUMN; i++) {
    //     available[process_number][i]
    //     = (allocation[process_number][i] + available[process_number][i]);
        
    //     available_current_value[i] = available[process_number][i];
    //     allocation[process_number][i] = 0;
    // }

    // Remove element in queue
}

/*
void removeElementInQueue(int executing_process, queue<int>& process_queue) {

    // Reference:
    // https://www.geeksforgeeks.org/how-to-remove-a-specific-element-from-queue/

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
*/


void buildBankersAlgorithm() {

    int process_number = 0;
    // = process_queue.size();
    // cout << "Process Number: " << process_number << endl;

    int process_counter = 0;
    // while (!process_queue.empty() /*process_counter != 5*/) {
        
    //     if (isExecutable(process_counter) == true) {
    //         cout << "TRUE" << endl;

    //         // delete 1 in process counter

    //         executeProcess(process_number); // pop & print
    //         printTable();

    //         removeElementInQueue(process_number, process_queue);
    //         cout << "Executing P" << process_number << endl;
    //         cout << "\n"; printQueue(process_queue);

    //         process_counter = 0;
    //         // process_number++;
    //         cout << "Counter: " << process_counter << endl;
    //         cout << "P number:" << process_number << endl;
    //         // available += allocation[][]
    //     }
    //     else if (isExecutable(process_counter) == false) {
    //         cout << "FALSE" << endl;
    //         cout << "P" << process_counter << endl;
    //         process_counter++;
    //         process_number++;
    //         cout << "Counter: " << process_counter << endl;
    //         cout << "P number:" << process_number;

    //         //process_number = process_counter;
    //     }
    //     cout << "\n======== ======== ======== ======== ========\n" << endl;
    // }
}


void deallocation() {

}

/*
int writeOutputFile() {
    ofstream outputFile("output.txt");
}
*/

int main() {

    readInputFile();
    
    cout << "===== ===== Initial Value from a Table ===== =====" << endl;
    printTable();
    // cout << "\n"; printQueue(process_queue);



    // cout << "\n===== ===== ===== Running ===== ===== =====" << endl;
    // buildBankersAlgorithm();

    deallocation();

    return 0;

}