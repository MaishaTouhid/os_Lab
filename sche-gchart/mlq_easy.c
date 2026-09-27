#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], q[n], wt[n], tat[n];

    printf("Enter burst time and queue number (1 = High Priority, 2 = Low Priority) of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P%d - Queue (1 or 2): ", i + 1);
        scanf("%d", &q[i]);
    }

    int time = 0;
    int gantt[1000], g = 0;

    // Queue 1 (high priority) er shob process age chole
    for (int i = 0; i < n; i++) {
        if (q[i] == 1) {
            wt[i] = time;
            time += bt[i];
            tat[i] = time;
            gantt[g++] = i + 1;
        }
    }

    // Tarpor Queue 2 (low priority) er process gulo chole
    for (int i = 0; i < n; i++) {
        if (q[i] == 2) {
            wt[i] = time;
            time += bt[i];
            tat[i] = time;
            gantt[g++] = i + 1;
        }
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBurst\tQueue\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], q[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    // ------- Gantt Chart -------
    printf("\nGantt Chart:\n| ");
    for (int i = 0; i < g; i++) printf("P%d | ", gantt[i]);
    printf("\n");

    return 0;
}
