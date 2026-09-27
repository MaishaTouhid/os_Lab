#include <stdio.h>
// Gantt Chart Function
void ganttChart(int at[], int bt[], int n) {

    int rt[n];

    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    printf("\nGantt Chart:\n");

    int time = 0;
    int done = 0;

    while (done < n) {

        int idx = -1;
        int minRemaining = 9999;

        for (int i = 0; i < n; i++) {

            if (at[i] <= time &&
                rt[i] > 0 &&
                rt[i] < minRemaining) {

                minRemaining = rt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        printf("| P%d ", idx + 1);

        rt[idx]--;
        time++;

        if (rt[idx] == 0) {
            done++;
        }
    }

    printf("|\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], wt[n], tat[n], completed[n];

    printf("Enter arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // remaining time
        completed[i] = 0;
    }

    int time = 0, done = 0;

    // Run time unit by unit until all processes finish
    while (done < n) {
        int idx = -1;
        int minRemaining = 9999;

        // Find process with shortest remaining time among arrived processes
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < minRemaining) {
                minRemaining = rt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            // No process available, move time forward
            time++;
            continue;
        }

        rt[idx]--;
        time++;

        if (rt[idx] == 0) {
            completed[idx] = 1;
            done++;
            tat[idx] = time - at[idx];
            wt[idx] = tat[idx] - bt[idx];
        }
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
  
        // Gantt Chart Function Call
    ganttChart(at, bt, n);

    return 0;
}
