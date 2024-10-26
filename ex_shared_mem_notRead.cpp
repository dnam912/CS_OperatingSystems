#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

int main() {

    // Creates and opens a shared memory object requesting to OS.
    int shm_fd = shm_open("/my_mailbox", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, 1024); // Decide the size of shared mem.

    // Maps the shared memory object into the process's address space.
    void* shared_mem = mmap(0, 1024, PROT_WRITE, MAP_SHARED, shm_fd, 0);


    // ========================================================

    pid_t pid = fork();

    // Mom cannot read the message
    if (pid == 0) { // Child Only

        sleep(3);
    
        // Copies the message into shared memory.
        const char* message = "Hi mom!!!";
        memcpy(shared_mem, message, strlen(message) + 1);
        

    } else if (pid > 0) { // Parent Only

        cout << "Mom reads: " << static_cast<char*>(shared_mem) << endl;

        // "wait" must make mom read the message from child.
        wait(NULL);  // Wait for the child process to finish
    }


    // Destroy shared memory - Deallocation
    munmap(shared_mem, 1024);
    close(shm_fd);
    shm_unlink("/my_mailbox");


    return 0;
}











