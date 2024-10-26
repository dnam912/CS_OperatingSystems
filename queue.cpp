#include <iostream>
#include <thread>
#include <queue>
#include <mutex>

using namespace std;

int counter = 0;
int MAX_SIZE = 10;

queue<int> bounded_buffer;

int main() {
    cout << "Queue input" << endl;
    for (int i = 0; i < MAX_SIZE; i++) {
            bounded_buffer.push(i);
            cout << i << " ";
    }
    cout << endl;

    cout << "Queue pop" << endl;
    while(!bounded_buffer.empty()) {
            cout << bounded_buffer.front() << " ";
            bounded_buffer.pop();
    }
    cout << endl;

    cout << "Completed" << endl;
}