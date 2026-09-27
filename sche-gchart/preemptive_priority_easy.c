#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n], rt[n], wt[n], tat[n];

    printf("Enter arrival time, burst time and priority (lower number = higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("P%d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P%d - Priority: ", i + 1);
        scanf("%d", &pr[i]);
        rt[i] = bt[i];
    }

    int time = 0, done = 0;
    int gantt[1000], g = 0;   // gantt chart e kon process cholche seta save kora hocche

    while (done < n) {
        int idx = -1, best = 999999;

        // arrive kora process gulor moddhe sobcheye bhalo priority (choto number) khoja hocche
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && pr[i] < best) {
                best = pr[i];
                idx = i;
            }
        }

        if (idx == -1) { time++; continue; }

        rt[idx]--;
        gantt[g++] = idx + 1;
        time++;

        if (rt[idx] == 0) {
            tat[idx] = time - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            done++;
        }
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    // ------- Gantt Chart -------
    // ekই process poropori koto unit cholche seta merge kore dekhano hocche
    printf("\nGantt Chart:\n| ");
    int t = 0;
    for (int i = 0; i < g; i++) {
        if (i == g - 1 || gantt[i] != gantt[i + 1]) {
            printf("P%d | ", gantt[i]);
        }
    }
    printf("\n0");
    for (int i = 0; i < g; i++) {
        t++;
        if (i == g - 1 || gantt[i] != gantt[i + 1]) {
            printf(" %d", t);
        }
    }
    printf("\n");

    return 0;
}
