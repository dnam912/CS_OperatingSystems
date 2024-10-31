#include <iostream>
#include <queue>
#include <mutex>

#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>

#include <condition_variable> // Add

using namespace std;


// BOUNDED BUFFER
const char* SHARED_MEM_NAME = "/my_shared_memory";
const int BUFFER_SIZE = 2; // The table can only hold two items at the same time.
int index_counter;

struct SharedMemory {
    // queue<int> buffer;
    int buffer[BUFFER_SIZE];
    int counter = 0;
    int producer_in = 0;
}

// SEMAPHORES
// int shm_open(const char *name, int oflag, mode_t mode);
// int shm_unlink(const char *name);
sem_t mutex, full, empty
int pshared = 1;


void produce() {
    // Create shared memory object
    int shm_object = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    
    // Decide the size of shared mem.
    // ftruncate(shm_object, 1024);

    // Map the shared_mem object into the process's address space
    SharedMemoryr* SHARED_MEM = (SharedMemory*)mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_object, 0);


    /* 
    INITIALIZE SEMAPHORES
        sem_init(sem_t *sem, int pshared, unsigned value);
    */
    sem_init(&SHARED_MEM->mutex, pshared, 1); // sem_mutex initialized to value 1 (binary semaphore)
    sem_init(&SHARED_MEM->full, pshared, 0); // sem_full initailzied to value 0 (counting semaphore)
    sem_init(&SHARED_MEM->empty, pshared, BUFFER_SIZE); // sem_empty initialized to value n (counting sempaphore)


    do {
        /*
        // produce an item

        wait(empty); // 
        wait(mutex); // 
        
        // add to buffer

        signal(mutex); // 
        signal(full); // 
        */


        munmap(sharedBuffer, sizeof(SharedBuffer));
        close(shm_object);

    } while (true);
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
        return 0;
    } else if (pid > 0) {
        wait(NULL);
    } else {
        cerr << "Fork failed" << endl;
        return 1;
    }

    return 0;
}
