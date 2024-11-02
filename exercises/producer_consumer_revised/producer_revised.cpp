#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <condition_variable>
#include <string>
#include <semaphore.h>
#include <queue>
#include <mutex>
#include <atomic>

using namespace std;

struct SharedMemory {
    atomic<int> cake;
    sem_t sem;
};

const char* SHARED_MEM_NAME = "/my_shared_memory";
SharedMemory* sharedMemory;

void producer(string id, pid_t pid) {
    int childProduced = 0;
    int parentProduced = 0;

    while (true) {
        
        if (pid == 0) { // Child
            sem_wait(&sharedMemory->sem);
            sharedMemory->cake++;
            childProduced++;
            cout << "Producer: " << id << " - Produced: " << childProduced << endl;
            sem_post(&sharedMemory->sem);
            if (childProduced == 4) {
                break;
            }
            sleep(1);
        } else if (pid > 0) { // Parent
            sem_wait(&sharedMemory->sem);
            sharedMemory->cake++;
            parentProduced++;
            cout << "Producer: " << id << " - Produced: " << parentProduced << endl;
            sem_post(&sharedMemory->sem);
            if (parentProduced == 4) {
                break;
            }
            sleep(1);
        }
    }


    cout << "Producer: " << id << " - " << getpid() << endl;
    
}

int main() {
    int shm_object = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_object, sizeof(SharedMemory));
    sharedMemory = (SharedMemory*)mmap(0, sizeof(SharedMemory),
                                PROT_READ | PROT_WRITE, MAP_SHARED, shm_object, 0);
    close(shm_object);
    sem_init(&sharedMemory->sem, 1, 1); // threads = 0, process = 1 (second parameters)
    new (&sharedMemory->cake) atomic<int>(0); 

    pid_t pid = fork();
    if (pid == 0) { // Child
        producer("child", pid);
    } else if (pid > 0) { // Parent
        producer("parent", pid);
        wait(0);

        /********** Destroy Shared Memory  **********/
        munmap(sharedMemory, sizeof(sharedMemory));
        sem_destroy(&sharedMemory->sem);
        shm_unlink(SHARED_MEM_NAME);
    } else {
        cout << "Fork() failed!" << endl;
    }

    return 0;
}
