#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {

    cout << "PARENT PID: " << getpid() << endl;

    pid_t pid[3];

    for (int i = 0; i < 3; i++) {
        pid[i] = fork();
    }

    // if (pid > 0) { // Parent Only
    
    //     wait(NULL);  // Wait for the child process to finish

    // } else if (pid == 0) { // Child Only
    // }

        cout << "I AM CHILD with PID:  " << pid[0] << endl;
        cout << "I AM CHILD with PID:  " << pid[1] << endl;
        cout << "I AM CHILD with PID:  " << pid[2] << endl;

    wait(0);
    return 0;
}











