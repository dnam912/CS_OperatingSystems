#include <iostream>
#include <thread>
#include <queue>
#include <mutex>

using namespace std;

/* Programming Assignment #1
Shared memory
You need shared memory to build the buffer accessible by two processes.
Yes, two processes. 

Mutual exclusion
Use Semaphore 


In this programming assignment, you must provide the source codes, documents, and examples in detail on Github. They will be counted for the final score. Please submit the link to the project on Github. 

Requirements:
	•	You are required to use C/C++ in Linux/Unix. You can consider installing VirtualBox in your non-Linux environment.
	•	Programs must succeed in compilation and execution as required (80 points)
	•	Readme, documentation and example are required (20 points).

Topic: Producer-Consumer Problem

The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

We expect to use these two programs (producer and consumer) like this:

$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &
*/

int counter = 0;
int MAX_SIZE = 10;
int n = 2;

// mutex
// : A binary semaphore which is used to acquire and release the lock
//mutex producer_mutex;
//mutex consumer_mutex;
queue<int> bounded_buffer;

void consume(int n) {
    do {
        /*
        wait(full); // wait until full > 0 and decrement full
        wait(_mutex_); // acquire lock
         // consume data from buffer

        signal(_mutex_); // release lock
        signal(empty); // increment empty
        */

    } while (true);
}

int main() {
    cout << "Creating threads" << endl;
    thread producer(produce);
    // thread consumer(consume, 1);


    cout << "Threads join" << endl;
    producer.join();
    // consumer.join();

    cout << "Completed" << endl;
}