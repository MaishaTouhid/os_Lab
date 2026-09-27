#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], pr[n], wt[n], tat[n];

    printf("Enter burst time and priority of each process (lower number = higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P%d - Priority: ", i + 1);
        scanf("%d", &pr[i]);
    }

    // Sort by priority (Bubble Sort), keep burst time matched
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pr[j] > pr[j + 1]) {
                int temp = pr[j];
                pr[j] = pr[j + 1];
                pr[j + 1] = temp;

                temp = bt[j];
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
    printf("\nProcess\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t\t%d\t%d\n", i + 1, bt[i], pr[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
