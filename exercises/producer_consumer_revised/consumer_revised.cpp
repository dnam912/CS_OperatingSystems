#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <mutex>
#include <condition_variable>
#include <string>
#include <semaphore.h>
#include <queue>
#include <atomic>

using namespace std;

const char* SHARED_MEM_NAME = "/my_shared_memory";

struct SharedMemory {
    atomic<int> cake;
    sem_t sem;
};

void consumer(string id, pid_t pid) {
    int childScore = 0;
    int parentScore = 0;

    int shm_fd = shm_open(SHARED_MEM_NAME, O_RDWR, 0666);
    SharedMemory* sharedMemory = (SharedMemory*)
        mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    while (true) {

        if (pid == 0) { // Child
            sem_wait(&sharedMemory->sem);
            sharedMemory->cake--;
            childScore++;
            cout << "Consumer: " << id << " - Score: " << childScore << endl;
            sem_post(&sharedMemory->sem);
            if (childScore == 2) {
                break;
            }
            sleep(1);
        } else if (pid > 0) { // Parent
            sem_wait(&sharedMemory->sem);
            sharedMemory->cake--;
            parentScore++;
            cout << "Consumer: " << id << " - Score: " << parentScore << endl;
            sem_post(&sharedMemory->sem);
            if (parentScore == 2) {
                break;
            }
            sleep(1);
        }
    }

    cout << "Consumer: " << id << " - " << getpid() << endl;
    
}

int main() {


    pid_t pid = fork();

    if (pid == 0) { // Child
        consumer("child", pid);
    } else if (pid > 0) { // Parent
        consumer("parent", pid);
        wait(0);
    } else {
        cout << "Fork() failed!" << endl;
    }

    shm_unlink(SHARED_MEM_NAME);
    return 0;
}


