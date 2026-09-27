#include <stdio.h>

// Gantt Chart Function
void ganttChart(int bt[], int n, int quantum) {

    int rt[n];

    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    printf("\nGantt Chart:\n");

    int time = 0;
    int done = 0;

    while (done < n) {

        for (int i = 0; i < n; i++) {

            if (rt[i] > 0) {

                printf("| P%d ", i + 1);

                if (rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                }

                else {
                    time += rt[i];
                    rt[i] = 0;
                    done++;
                }
            }
        }
    }

    printf("|\n");

    // Time values
    printf("0");

    time = 0;
    done = 0;

    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    while (done < n) {

        for (int i = 0; i < n; i++) {

            if (rt[i] > 0) {

                if (rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                }

                else {
                    time += rt[i];
                    rt[i] = 0;
                    done++;
                }

                printf("%5d", time);
            }
        }
    }

    printf("\n");
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], wt[n], tat[n];

    printf("Enter burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int time = 0;
    int done = 0;

    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                if (rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                } else {
                    time += rt[i];
                    wt[i] = time - bt[i];
                    rt[i] = 0;
                    done++;
                }
            }
        }
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    // Gantt Chart Function Call
    ganttChart(bt, n, quantum);

    return 0;
}
