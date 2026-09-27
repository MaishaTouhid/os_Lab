#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], wt[n], tat[n], level[n];
    // level[i] = process ta ekhon kon queue te ache (0, 1, ba 2)

    printf("Enter burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        level[i] = 0;   // shob process Queue 0 diye shuru hoy
    }

    int quantum[3] = {2, 4, 9999};   // Queue0=2, Queue1=4, Queue2=onek boro (FCFS er moto)
    int time = 0, done = 0;
    int gantt[10000], g = 0;

    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                int q = quantum[level[i]];
                int run = (rt[i] < q) ? rt[i] : q;

                gantt[g++] = i + 1;
                time += run;
                rt[i] -= run;

                if (rt[i] == 0) {
                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];
                    done++;
                } else if (level[i] < 2) {
                    level[i]++;   // shesh na hole porer (nichu) queue te namiye deya hocche
                }
            }
        }
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    // ------- Gantt Chart -------
    printf("\nGantt Chart:\n| ");
    for (int i = 0; i < g; i++) printf("P%d | ", gantt[i]);
    printf("\n");

    return 0;
}
