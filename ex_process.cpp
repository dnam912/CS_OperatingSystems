#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {




    for (int i = 0; i <10; i++) {

        cout << "MY PID: " << getpid() << endl;
        wait(1);
    }



    return 0;
}














