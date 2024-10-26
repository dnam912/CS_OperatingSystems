#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>

using namespace std;

int countingSemaphore = 0;
mutex producerMutex;

queue<int> bounded_buffer;

int n = 2;

void produce(int n) {
    do {
        /*
        wait(empty); // wait until empty > 0 and decrement empty
        wait(_mutex_); // acquire lock
         // produce data from buffer

        signal(_mutex_); // release lock
        signal(full); // increment full
        */

       int n = 2;

        std::this_thread::sleep_for (std::chrono::seconds(n));
        std::cout << "pause of " << n << " seconds ended\n";
       
    } while (true);
}

int main() {
    cout << "Creating Threads" << endl;
    thread producer(produce, 0);
    thread producer1(produce, 1);
    producer.join();
    producer1.join();
    cout << "Join" << endl;


    // produce();
    return 0;
}