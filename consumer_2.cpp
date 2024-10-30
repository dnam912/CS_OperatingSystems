#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable> // Add

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#include <unistd.h>
        #include <ctype.h>
        #include <stdio.h>
        #include <stdlib.h>

using namespace std;


mutex mtx;
condition_variable cv; 

const char* SHARED_MEM_NAME = "/my_shared_memory";

// BOUNDED BUFFER
const int BUFFER_SIZE = 10;
int index_counter;

struct SharedMemory {
        queue<int> bounded_buffer;    
}

// int shm_open(const char *name, int oflag, mode_t mode);
// int shm_unlink(const char *name);


void consumer() {
        // Create shared memory object
        int shm_fd = shm_open("/my_shm", O_CREAT | O_RDWR, 0666);

}

int main() {
        
}
