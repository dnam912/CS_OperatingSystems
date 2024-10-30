#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

const char* SHARED_MEM_NAME = "/my_mailbox";
const int SHARED_MEM_SIZE = 4096;

struct SharedMemory {
    pthread_mutex_t mutex;
    int data;
};

int main() {

    // ================= Initialize Share Memory =======================
    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHARED_MEM_SIZE); 
    void* shared_mem = mmap(0, SHARED_MEM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    SharedMemory* sharedMem = (SharedMemory*)
            mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // =============== set mutex to be functioned =============
    pthread_mutexattr_t mutexAttr;
    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&sharedMem->mutex, &mutexAttr);

    // ========================================================

    pid_t pid = fork();
    
    if (pid == 0) { // Child Only
        pthread_mutex_lock(&sharedMem->mutex);
        sleep(3);
        sharedMem->data = 1;
        pthread_mutex_unlock(&sharedMem->mutex);

    } else if (pid > 0) { // Parent Only

        sleep(2);
    
        while(true) {
            if (sharedMem->data == 1) {
                break;
            }
        }
        cout << "Mom reads: " << sharedMem->data << endl;

        wait(NULL);  
        
    }


    // Destroy shared memory - Deallocation
    munmap(shared_mem, SHARED_MEM_SIZE);
    close(shm_fd);
    shm_unlink(SHARED_MEM_NAME);


    return 0;
}











