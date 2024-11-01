// GLOBAL INCLUDE FILES
#include <iostream>
#include <queue>
#include <mutex>

// LINUX HEADER FILES
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
// #include <condition_variable> // Add

#include <unistd.h>    // Needed for fork
#include <sys/wait.h>  // Needed for wait

using namespace std;


// BOUNDED BUFFER
const char* SHARED_MEM_NAME = "/my_shared_memory";
const int BUFFER_SIZE = 2; // The table can only hold two items at the same time.

// Assign 1 to one of parameters named 'pshared' when initializing semaphores
int pshared = 1; 

// INITIALIZE MAP FOR A BUFFER IN A SHARED MEMORY
struct SharedMemory {
    int buffer[BUFFER_SIZE];
    int index_counter;
    int consumer_out;

    // INITIALIZE SEMAPHORES
    sem_t mutex, full, empty;
};





void consume() {



/*
    do {
        
        wait(full); // wait until full > 0 and decrement full
        wait(mutex); // acquire lock
        
        // remove an item

        signal(mutex); // release lock
        signal(empty); // increment empty
        
        // consume data from buffer
        

    } while (true);
*/
}

int main() {
    // Fork to create processes (producer & consumer)
    pid_t pid = fork();
    /* PROCESSES
            (pid)
            /   \
    (producer)  (consumer)
    */
    
    if (pid == 0) {
        produce();
        return 0;
    } else if (pid > 0) {
        wait(NULL);
    } else {
        cerr << "Fork failed" << endl;
        return 1;
    }

    shm_unlink(SHARED_MEM_NAME);
}
