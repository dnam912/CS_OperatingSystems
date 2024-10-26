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


