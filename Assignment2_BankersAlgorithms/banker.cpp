// GLOBAL INCLUDE FILES
#include <iostream>
#include <queue>
#include <mutex>

// LINUX HEADER FILES
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>          // Needed for fork
#include <sys/wait.h>        // Needed for wait

using namespace std;

// Banker’s Algorithm for deadlock avoidance.

/*
Considering a system with five processes P0 through P4 and three resources of type A, B, C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances. Suppose at time t0 following snapshot of the system has been taken:


Implement the Banker’s algorithm to answer the following question： Is the system in a safe state? If Yes, then what is the safe sequence?

Input file (you should create an input file, e.g., .txt, with your customized format that stores the data that is provided in the table).  
Your code should print out the safe sequence if the system is safe.
*/

int main() {
    
}