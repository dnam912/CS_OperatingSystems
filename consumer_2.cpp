#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable> // Add

#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

        #include <ctype.h>
        #include <fcntl.h>
        #include <stdio.h>
        #include <stdlib.h>
        #include <sys/mman.h>
        #include <unistd.h>

using namespace std;

int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);


void consumer() {

}

int main() {

}