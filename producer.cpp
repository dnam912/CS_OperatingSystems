#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>

using namespace std;

int countingSemaphore = 0;
mutex producerMutex;

queue<int> bounded_buffer;

void produce() {
    do {

        wait(empty); // wait until empty > 0 and decrement empty
        wait(producerMutex); // acquire lock
        /*produce data from buffer*/

        signal(producerMutex); // release lock
        signal(full); // increment full


    } while (true);
}