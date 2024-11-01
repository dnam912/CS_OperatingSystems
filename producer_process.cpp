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
    int producer_in; // Items for producer

    // INITIALIZE SEMAPHORES
    sem_t mutex, full, empty;
};


void Produce() {
    // CREATE SHARED MEMORY OBJECT
    // :  int shm_open(const char *name, int oflag, mode_t mode);
    int shm_object = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    
    // DECIDE THE SIZE OF SHARED MEM
    ftruncate(shm_object, 1024);

    // Map the SHARED_MEM into the process's address space
    SharedMemory* SHARED_MEM = (SharedMemory*)mmap(0, sizeof(SharedMemory),
                                PROT_READ | PROT_WRITE, MAP_SHARED, shm_object, 0);
    
    SHARED_MEM->index_counter = 0;  // Assign zero in variables of SHARED MEM
    SHARED_MEM->producer_in = 0;    // Produce an item in the buffer

    // INITIALIZE SEMAPHORES
    // :  sem_init(sem_t *sem, int pshared, unsigned value);
    sem_init(&SHARED_MEM->mutex, pshared, 1);           // sem_mutex initialized to value 1 (binary semaphore)
    sem_init(&SHARED_MEM->full, pshared, 0);            // sem_full initailzied to value 0 (counting semaphore)
    sem_init(&SHARED_MEM->empty, pshared, BUFFER_SIZE); // sem_empty initialized to value n (counting sempaphore)


    /* PSEUDO CODE FOR PRODUCER
    do {
        // produce an item

        wait(empty); // wait until buffer's empty
        wait(mutex); // acquire lock
        
        // add to buffer

        signal(mutex); // release lock
        signal(full);  // an item in buffer
      
    } while (true);
    */
    for (int i = 0; i < BUFFER_SIZE; i++) {
        sem_wait(&SHARED_MEM->empty);  // Wait if buffer is full
        sem_wait(&SHARED_MEM->mutex);  // Lock mutex
        
        SHARED_MEM->buffer[SHARED_MEM->producer_in] = i;

        cout << "Produced: " << SHARED_MEM->buffer[SHARED_MEM->producer_in] << endl;
            
        SHARED_MEM->index_counter++;   // Increment the counter of current buffer index


        sem_post(&SHARED_MEM->mutex);  // Unlock mutex
        sem_post(&SHARED_MEM->full);   // Signal that buffer has an item

        sleep(1); // Delay the execution (1 second)
    }


    // DESTROY ASSIGNED SEMAPHORES
    sem_destroy(&SHARED_MEM->mutex);
    sem_destroy(&SHARED_MEM->full);
    sem_destroy(&SHARED_MEM->empty);

    // REMOVE THE MAP CONTAINING THE ADDRESS SPACE OF PROCESS
    munmap(&SHARED_MEM, sizeof(SharedMemory)); 

    // UNLINK SHARED MEMORY OBJECT
    // :  int shm_unlink(const char *name);
    shm_unlink(SHARED_MEM_NAME);
}

int main() {
    // Fork to create process 1
    pid_t pid = fork();

    /*    PROCESSES
            (pid)
            /   \
    (producer)  (consumer)
    */
    
    if (pid == 0) {
        Produce();
        return 0;
    } else if (pid > 0) {
        wait(NULL);
    } else {
        cerr << "Fork failed" << endl;
        return 1;
    }

    return 0;
}
