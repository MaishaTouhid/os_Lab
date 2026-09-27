#include <iostream>
#include <unistd.h>   // fork()
#include <sys/wait.h> // wait()

using namespace std;

int main() {

    // ===== Child 1 toiri kora holo =====
    pid_t pid1 = fork();

    if (pid1 == 0) {
        // eta child 1 er code
        cout << "Child 1: Addition kaj korche -> " << (5 + 10) << endl;
        _exit(0); // child 1 shesh
    }

    // ===== Child 2 toiri kora holo =====
    pid_t pid2 = fork();

    if (pid2 == 0) {
        // eta child 2 er code
        cout << "Child 2: String print korche -> Hello from child 2" << endl;
        _exit(0); // child 2 shesh
    }

    // ===== Child 3 toiri kora holo =====
    pid_t pid3 = fork();

    if (pid3 == 0) {
        // eta child 3 er code
        int sum = 0;
        for (int j = 1; j <= 5; j++) sum += j;
        cout << "Child 3: Loop chalaye sum ber korche -> " << sum << endl;
        _exit(0); // child 3 shesh
    }

    // ===== Eikhane sudhu Parent process ashbe =====
    // (kono child eikhane pouchabe na, karon shobai upore _exit(0) diye beriye geche)

    wait(NULL); // child 1 er jonno wait
    wait(NULL); // child 2 er jonno wait
    wait(NULL); // child 3 er jonno wait

    cout << "Parent: shob child process shesh hoyeche." << endl;

    return 0;
}