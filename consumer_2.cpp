#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable> // Add

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#include <unistd.h>
#include <semaphore.h>

        #include <ctype.h>
        #include <stdio.h>
        #include <stdlib.h>

using namespace std;


// mutex mtx;
condition_variable cv; 
sem_t mutex, full, empty

const char* SHARED_MEM_NAME = "/my_shared_memory";
int counter;

// BOUNDED BUFFER
const int BUFFER_SIZE = 10;
struct SharedMemory {
        queue<int> bounded_buffer;    
}

// INITIALIZE SEMAPHORES




void consume() {
    // int shm_open(const char *name, int oflag, mode_t mode);
    // int shm_unlink(const char *name);
    
    // Create shared memory object
    int fd = shm_open("/my_shm", O_CREAT | O_RDWR, 0666);


    do {
        /*
        wait(full); // wait until full > 0 and decrement full
        wait(mutex); // acquire lock
        
        // remove an item

        signal(mutex); // release lock
        signal(empty); // increment empty
        
        // consume data from buffer
        */

    } while (true);
}

int main() {
        
}
