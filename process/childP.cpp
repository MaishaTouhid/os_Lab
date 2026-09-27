#include <iostream>
#include <unistd.h>   // fork(), getpid()
#include <sys/wait.h> // wait()

using namespace std;

int main() {
    int n = 3; // কয়টা child process create করতে চাও

    for (int i = 1; i <= n; i++) {
        pid_t pid = fork(); // নতুন child process তৈরি হবে

        if (pid == 0) {
            // এই ব্লকটা child process এর মধ্যে execute হবে
            if (i == 1) {
                cout << "Child " << i << ": Addition kaj korche -> " 
                     << (5 + 10) << endl;
            }
            else if (i == 2) {
                cout << "Child " << i << ": String print korche -> "
                     << "Hello from child 2" << endl;
            }
            else if (i == 3) {
                cout << "Child " << i << ": Loop chalaye sum ber korche -> ";
                int sum = 0;
                for (int j = 1; j <= 5; j++) sum += j;
                cout << sum << endl;
            }

            _exit(0); // child process shesh, jate parent er code abar run na kore
        }
        // pid > 0 hole eta parent process, loop চলতেই থাকবে next child banate
    }

    // parent shob child process shesh howa porjonto wait korbe
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    cout << "Parent: shob child process shesh hoyeche." << endl;
    return 0;
}