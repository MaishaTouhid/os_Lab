#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int id, burstTime, waitingTime, turnaroundTime;
};

// Comparison function to sort by burst time
bool compare(Process a, Process b) {
    return a.burstTime < b.burstTime;
}

void sjfScheduling(Process processes[], int n) {
    sort(processes, processes + n, compare); // Sort by burst time

    processes[0].waitingTime = 0; // First process has no waiting time

    for (int i = 1; i < n; i++)
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;

    for (int i = 0; i < n; i++)
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
        cout << "P" << processes[i].id << "\t" << processes[i].burstTime << "\t\t"
             << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burstTime;
    }

    sjfScheduling(processes, n);

    return 0;
}
