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


// BOUNDED BUFFER
const char* SHARED_MEM_NAME = "/my_shared_memory";
const int BUFFER_SIZE = 2; // The table can only hold two items at the same time.

// Assign 1 to one of parameters named 'pshared' when initializing semaphores
int pshared = 1;

// INITIALIZE MAP FOR A BUFFER IN A SHARED MEMORY
struct SharedMemory {
    int buffer[BUFFER_SIZE];
    int index_counter;
    int consumer_out; // Items for consumer

    // INITIALIZE SEMAPHORES
    sem_t mutex, full, empty;
};

// INITIALIZE 'int item' TO STORE A CONSUMED ITEM
int item;


void Consume() { 
    // CREATE SHARED MEMORY OBJECT
    // :  int shm_open(const char *name, int oflag, mode_t mode);
    int shm_object = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    
    // DECIDE THE SIZE OF SHARED MEM
    ftruncate(shm_object, 1024);

    // Map the SHARED_MEM into the process's address space
    SharedMemory* SHARED_MEM = (SharedMemory*)mmap(0, sizeof(SharedMemory),
                                PROT_READ | PROT_WRITE, MAP_SHARED, shm_object, 0);

    SHARED_MEM->index_counter = 0;  // Assign zero in variables of SHARED MEM
    SHARED_MEM->consumer_out = 0;   // Without initializing consumer_out, it causes seg fault

    // INITIALIZE SEMAPHORES
    // :  sem_init(sem_t *sem, int pshared, unsigned value);
    sem_init(&SHARED_MEM->mutex, pshared, 1);           // sem_mutex initialized to value 1 (binary semaphore)
    sem_init(&SHARED_MEM->full, pshared, 0);            // sem_full initailzied to value 0 (counting semaphore)
    sem_init(&SHARED_MEM->empty, pshared, BUFFER_SIZE); // sem_empty initialized to value n (counting sempaphore)


    /* PSEUDO CODE FOR CONSUMER
    do {  
            wait(full);  // wait until buffer's full
            wait(mutex); // acquire lock
            
            // remove an item

            signal(mutex); // release lock
            signal(empty); // an empty space in buffer
            
            // consume data from buffer

    } while (true);
    */
    for (int i = (BUFFER_SIZE - 1); i >= 0; i--) {
        sem_wait(&SHARED_MEM->full);   // Wait if buffer is empty
        sem_wait(&SHARED_MEM->mutex);  // Lock mutex

        int item = SHARED_MEM->buffer[SHARED_MEM->consumer_out];    // Consume an item from the buffer
        
        cout << "Consumed: " << item << endl;                       // item == 1;
        
        // Sync the value of item & consumer_out
        SHARED_MEM->consumer_out = (SHARED_MEM->consumer_out - 1 + BUFFER_SIZE) % BUFFER_SIZE;

        SHARED_MEM->index_counter--;   // Decrement the counter of current buffer index


        sem_post(&SHARED_MEM->mutex);  // Unlock mutex
        sem_post(&SHARED_MEM->empty);  // Signal that buffer has nothing

        sleep(2); // Delay the execution (2 seconds)
    }


    // DESTROY ASSIGNED SEMAPHORES
    sem_destroy(&SHARED_MEM->mutex);
    sem_destroy(&SHARED_MEM->full);
    sem_destroy(&SHARED_MEM->empty);

    // REMOVE THE MAP CONTAINING THE ADDRESS SPACE OF PROCESS
    munmap(&SHARED_MEM, sizeof(SharedMemory)); 

    /* DO NOT UNLINK SHARED MEMORY OBJECT IN CONSUMER.CPP.
        OR PRODUCER AND CONSUMER WILL NOT INTERACT */
    shm_unlink(SHARED_MEM_NAME);    // because of unmapping before,
                                    // there might be some issues when unlinking shared memory object in the consumer.cpp
}


int main() {
    // Consume();

    
    // Fork to create process
    pid_t pid = fork();
    if (pid == 0) {
        Consume();
        return 0;
    } else if (pid > 0) {
        wait(NULL);
    } else {
        cerr << "Fork failed" << endl;
        return 1;
    }


    return 0;
}