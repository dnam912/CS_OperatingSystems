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

void consumer() {
    int shm_fd = shm_open(SHARED_MEM_NAME, O_RDWR, 0666);
    SharedBuffer* sharedBuffer = (SharedBuffer*)mmap(0, sizeof(SharedBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return sharedBuffer->count > 0 || done; });
        
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
    std::thread cons(consumer);
    cons.join();
    return 0;
}
