#include <stdio.h>

// Gantt Chart Function
void ganttChart(int bt[], int n) {

    printf("\nGantt Chart:\n");

    printf(" ");

    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf("  P%d   |", i + 1);
    }

    printf("\n ");

    for (int i = 0; i < n; i++) {
        printf("--------");
    }

    printf("\n0");

    int time = 0;

    for (int i = 0; i < n; i++) {
        time += bt[i];
        printf("%8d", time);
    }

    printf("\n");
}


int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n];

    printf("Enter burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Sort burst times in ascending order (Bubble Sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
            }
        }
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

       // Gantt Chart Function Call
    ganttChart(bt, n);

    return 0;
}
