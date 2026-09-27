#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    int n = 3;

    for (int i = 1; i <= n; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {

            if (i == 1)
            {
                cout << "Child " << i << ": Addition work -> "
                     << (5 + 10) << endl;
            }
            else if (i == 2)
            {
                cout << "Child " << i << ":  print String  -> "
                     << "Hello from child 2" << endl;
            }
            else if (i == 3)
            {
                cout << "Child " << i << ": create sum using loop -> ";
                int sum = 0;
                for (int j = 1; j <= 5; j++)
                    sum += j;
                cout << sum << endl;
            }

            _exit(0);
        }
    }

    for (int i = 0; i < n; i++)
    {
        wait(NULL);
    }

    cout << "Parent: all child process completed." << endl;
    return 0;
}