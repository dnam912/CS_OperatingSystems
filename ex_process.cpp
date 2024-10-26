#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {

    for (int i = 0; i < 0; i++) {
        cout << "MY PID: " << getpid() << endl;
        sleep(1); // The process is alive and just sleeps for a second
                  // It isn't dead, so PID is the sames until the end of looping.
    }

    cout << "PARENT PID: " << getpid() << endl;

    pid_t pid = fork();


    if (pid < 0) {
        std::cerr << "Fork failed" << std::endl;
        return 1;
    } else if (pid == 0) { // Activated in child only
        // Child process
        for (int i = 0; i < 5; i++) {
            cout << "Child PID: " << getpid() << endl;
            sleep(1);
        }
    } else { // Activated on parent & child
        // Parent process
        cout << "Parent PID: " << getpid() << "I am waiting..." << endl;
        cout << " Child PID: " << pid << "I am done!!!!" << endl;
        wait(NULL);  // Wait for the child process to finish
    }

    cout << "Parent PID: " << getpid() << "I finish..." << endl;
    cout << " Child PID: " << pid << "I finish!!!!" << endl;

    return 0;
}














