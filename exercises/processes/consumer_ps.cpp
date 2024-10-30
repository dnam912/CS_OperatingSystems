#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <mutex>
#include <condition_variable>

const char* SHARED_MEM_NAME = "/my_shared_memory";
const unsigned int BUFFER_SIZE = 10;
std::mutex mtx;
std::condition_variable cv;
bool done = false;

struct SharedBuffer {
    int buffer[BUFFER_SIZE];
    int count;
};

void consumer() {
    int shm_fd = shm_open(SHARED_MEM_NAME, O_RDWR, 0666);
    SharedBuffer* sharedBuffer = (SharedBuffer*)mmap(0, sizeof(SharedBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        while (sharedBuffer->count == 0 && !done) cv.wait(lock);
        
        if (done && sharedBuffer->count == 0) break;
        
        int item = sharedBuffer->buffer[--sharedBuffer->count];
        std::cout << "Consumed: " << item << std::endl;
        
        cv.notify_all();
    }

    munmap(sharedBuffer, sizeof(SharedBuffer));
    close(shm_fd);
    shm_unlink(SHARED_MEM_NAME);
}

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        consumer();
        return 0;
    } else if (pid > 0) {
        wait(NULL);
    } else {
        std::cerr << "Fork failed." << std::endl;
        return 1;
    }
    return 0;
}


/*
/////////////////////////////////
#include <iostream>
#include <queue>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

const int BUFFER_SIZE = 10;

struct SharedMemory {
    std::queue<int> buffer;
    sem_t mutex, full, empty;
};

int main() {
    // Create shared memory object
    int shm_fd = shm_open("/my_shm", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedMemory));
    SharedMemory* shared_mem = (SharedMemory*)mmap(NULL, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize semaphores
    sem_init(&shared_mem->mutex, 1, 1); 
    sem_init(&shared_mem->full, 1, 0);
    sem_init(&shared_mem->empty, 1, BUFFER_SIZE); 

    // Fork to create producer and consumer processes
    pid_t pid = fork();

    if (pid == 0) { // Child process (Producer)
        for (int i = 1; i <= 20; ++i) {
            sem_wait(&shared_mem->empty); 
            sem_wait(&shared_mem->mutex);

            shared_mem->buffer.push(i);
            std::cout << "Producer produced: " << i << std::endl;

            sem_post(&shared_mem->mutex);
            sem_post(&shared_mem->full); 

            sleep(1); 
        }
    } else if (pid > 0) { // Parent process (Consumer)
        for (int i = 1; i <= 20; ++i) {
            sem_wait(&shared_mem->full); 
            sem_wait(&shared_mem->mutex);

            int item = shared_mem->buffer.front();
            shared_mem->buffer.pop();
            std::cout << "Consumer consumed: " << item << std::endl;

            sem_post(&shared_mem->mutex);
            sem_post(&shared_mem->empty); 

            sleep(2); 
        }
    } else {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    // Clean up (in parent process)
    if (pid > 0) {
        sem_destroy(&shared_mem->mutex);
        sem_destroy(&shared_mem->full);
        sem_destroy(&shared_mem->empty);
        munmap(shared_mem, sizeof(SharedMemory));
        shm_unlink("/my_shm");
    }

    return 0;
}
*/