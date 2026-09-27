#include <iostream>
using namespace std;

void roundRobin(int processes[], int n, int burstTime[], int timeQuantum) {
    int remainingTime[n], waitingTime[n] = {0}, turnaroundTime[n] = {0};
    for (int i = 0; i < n; i++)
        remainingTime[i] = burstTime[i];

    int time = 0; // Current time

    while (true) {
        bool done = true;

        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = false;
                if (remainingTime[i] > timeQuantum) {
                    time += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    time += remainingTime[i];
                    waitingTime[i] = time - burstTime[i];
                    remainingTime[i] = 0;
                }
            }
        }

        if (done)
            break;
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++)
        turnaroundTime[i] = burstTime[i] + waitingTime[i];

    // Print results
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
        cout << "P" << processes[i] << "\t" << burstTime[i] << "\t\t"
             << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
}

int main() {
    int n, timeQuantum;
    cout << "Enter number of processes: ";
    cin >> n;

    int processes[n], burstTime[n];
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        cout << "Enter burst time for process " << processes[i] << ": ";
        cin >> burstTime[i];
    }

    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    roundRobin(processes, n, burstTime, timeQuantum);

    return 0;
}
