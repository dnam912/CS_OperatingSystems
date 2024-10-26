
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

const char* SHARED_MEM_NAME = "/my_shared_memory";
const unsigned int BUFFER_SIZE = 10;
std::mutex mtx;
std::condition_variable cv;
bool done = false;

struct SharedBuffer {
    int buffer[BUFFER_SIZE];
    int count;
};

void producer(int n) {
    int shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedBuffer));
    SharedBuffer* sharedBuffer = (SharedBuffer*)mmap(0, sizeof(SharedBuffer), PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sharedBuffer->count = 0;

    for (int i = 0; i < n; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return sharedBuffer->count < BUFFER_SIZE; });
        
        sharedBuffer->buffer[sharedBuffer->count++] = i;
        std::cout << "Produced: " << i << std::endl;
        
        cv.notify_all();
    }

    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    cv.notify_all();
    
    munmap(sharedBuffer, sizeof(SharedBuffer));
    close(shm_fd);
}

int main() {
    int n = 20;
    std::thread prod(producer, n);
    prod.join();
    return 0;
}


























