#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Banker’s Algorithm for deadlock avoidance.

/*
Considering a system with five processes P0 through P4 and three resources 
of type A, B, C. Resource type A has 10 instances, B has 5 instances and 
type C has 7 instances. Suppose at time t0 following snapshot of the system 
has been taken:

Implement the Banker’s algorithm to answer the following question： 
Is the system in a safe state? If Yes, then what is the safe sequence?

Input file (you should create an input file, e.g., .txt, with your customized 
format that stores the data that is provided in the table).  
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


// PRINT TABLE
const int row = 5;
const int column = 3;

int resources_allocation[5][3] = {{0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2}};
int resources_max[5][3] = {{7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3}};
int resources_available[row][column];


// PRINT STATES
int processes[5];
string safety[2] = {"Safe", "Unsafe"};


void PrintArrays() {
    
    cout << "Prints Allocation" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << resources_allocation[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Prints Max" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << resources_max[i][j] << " ";
        }
        cout << endl;
    }


    /*
    cout << "Prints Available" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            // cout << allocation[i][j] << " ";
        }
        cout << endl;
    }*/

}


int main() {

    PrintArrays();


    return 0;
}