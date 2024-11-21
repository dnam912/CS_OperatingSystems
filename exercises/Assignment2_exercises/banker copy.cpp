#include <iostream>
#include <vector>

using namespace std;

// Banker’s Algorithm for deadlock avoidance.

/*
Considering a system with five processes P0 through P4 and three resources of type A, B, C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances. Suppose at time t0 following snapshot of the system has been taken:


Implement the Banker’s algorithm to answer the following question： Is the system in a safe state? If Yes, then what is the safe sequence?

Input file (you should create an input file, e.g., .txt, with your customized format that stores the data that is provided in the table).  
Your code should print out the safe sequence if the system is safe.
*/



/* vector<vector<int>>& allocation(int row, int column) {

    row = 5;
    column = 3;
    static vector<vector<int>> matrices;
    
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            matrices[j].push_back(allocationA);
        }
    }


    return matrices;
} */



int main() {

    int allocationA[5][1] = {0, 2, 3, 2, 0};
    int allocationB[5][1] = {1, 0, 0, 1, 0};
    int allocationC[5][1] = {0, 0, 2, 1, 2};

    int row = 5;
    int column = 3;
    int allocation[row][column];

    for (int i = 0; i <= column; i++) {
        for (int j = 0; j < row; j++) {
            allocation[j][i] = allocationA[j][i];
        }
    }


    cout << "Print arrays" << endl;
    for (int i = 0; i <= column; i++) {
        for (int j = 0; j < row; j++) {
            cout << allocationA[j][i] << " ";
        }
        cout << endl;
    }
    
}