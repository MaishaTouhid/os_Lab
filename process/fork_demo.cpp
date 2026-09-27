#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {
    pid_t pid;

    // Parent PID প্রিন্ট করা হচ্ছে (fork() করার আগে)
    cout << "Before fork() -> Parent PID: " << getpid() << endl;

    // fork() system call দিয়ে child process তৈরি করা হচ্ছে
    pid = fork();

    if (pid < 0) {
        // fork() ব্যর্থ হলে
        cerr << "Fork failed!" << endl;
        return 1;
    }
    else if (pid == 0) {
        // এই ব্লক শুধু Child process এক্সিকিউট করবে
        cout << "\nChild Process:" << endl;
        cout << "  Child PID  : " << getpid() << endl;
        cout << "  Parent PID (PPID) of child: " << getppid() << endl;
        cout << "  Child is executing...\n" << endl;

        // Child process এখানে terminate হচ্ছে
        cout << "  Child process terminating." << endl;
        _exit(0);
    }
    else {
        // এই ব্লক শুধু Parent process এক্সিকিউট করবে
        cout << "\nParent Process:" << endl;
        cout << "  Parent PID : " << getpid() << endl;
        cout << "  Created Child PID: " << pid << endl;
        cout << "  Parent is executing...\n" << endl;

        // Parent, child শেষ হওয়া পর্যন্ত wait করছে
        wait(NULL);

        cout << "  Child has terminated. Now Parent process terminating." << endl;
    }

    return 0;
}
