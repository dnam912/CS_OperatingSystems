/*
#include <iostream>
#include <queue>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

struct SharedMemoryQueue {
    std::queue<int> data;
    sem_t mutex;
    sem_t full;
    sem_t empty;
};

int main() {
    const char* shmName = "shared_queue";
    const int queueSize = 10;

    std::cout << "DEBUG_1" << std::endl;

    // Create shared memory
    int shmFd = shm_open(shmName, O_CREAT | O_RDWR, 0666);
    
    if (shmFd == -1) {
        perror("shm_open");
        return 1;
    }

    std::cout << "DEBUG_2" << std::endl;
    ftruncate(shmFd, sizeof(SharedMemoryQueue));

    SharedMemoryQueue* queue = (SharedMemoryQueue*)mmap(0, sizeof(SharedMemoryQueue), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
    if (queue == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Initialize semaphores
    sem_init(&queue->mutex, 1, 1);
    sem_init(&queue->full, 1, 0);
    sem_init(&queue->empty, 1, queueSize);

    // Producer process
    for (int i = 0; i < queueSize; ++i) {
        sem_wait(&queue->empty); 
        sem_wait(&queue->mutex); 

        std::cout << "Producer pushes" << std::endl;
        queue->data.push(i); // seg fault
        std::cout << "DEBUG_3" << std::endl;
        std::cout << "Producer produced: " << i << std::endl;

        sem_post(&queue->mutex);
        sem_post(&queue->full); 
    }

    std::cout << "DEBUG_4" << std::endl;
    // Unmap shared memory and close file descriptor
    munmap(queue, sizeof(SharedMemoryQueue));
    close(shmFd);
    shm_unlink(shmName);

    return 0;
}
*/

#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

const int BUFFER_SIZE = 2;
const char* SEM_MUTEX = "/sem_mutex";
const char* SEM_FULL = "/sem_full";
const char* SEM_EMPTY = "/sem_empty";

struct SharedBuffer {
    int buffer[BUFFER_SIZE];
    int in = 0;
    int count = 0;
};

void producer(int n) {
    // Create shared memory
    int shmid = shmget(1234, sizeof(SharedBuffer), IPC_CREAT | 0666);
    SharedBuffer* sharedBuffer = (SharedBuffer*)shmat(shmid, nullptr, 0);

    // Open or create semaphores
    sem_t* mutex = sem_open(SEM_MUTEX, O_CREAT, 0644, 1);
    sem_t* full = sem_open(SEM_FULL, O_CREAT, 0644, 0);
    sem_t* empty = sem_open(SEM_EMPTY, O_CREAT, 0644, BUFFER_SIZE);

    int item = 1;

    for (int i = 0; i < n; ++i) {
        sem_wait(empty);
        sem_wait(mutex);

        // Produce an item and add it to the buffer
        sharedBuffer->buffer[sharedBuffer->in] = item;
        std::cout << "Producer produced: " << item << std::endl;
        sharedBuffer->in = (sharedBuffer->in + 1) % BUFFER_SIZE;
        sharedBuffer->count++;
        item++;

        sem_post(mutex);
        sem_post(full);
        sleep(1);
    }

    // Cleanup
    sem_close(mutex);
    sem_close(full);
    sem_close(empty);
    shmdt(sharedBuffer);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./producer <number_of_items>\n";
        return 1;
    }
    int n = std::stoi(argv[1]);
    producer(n);

    // Unlink semaphores when producer is done
    sem_unlink(SEM_MUTEX);
    sem_unlink(SEM_FULL);
    sem_unlink(SEM_EMPTY);

    std::cout << "Producer has finished.\n";
    return 0;
}
