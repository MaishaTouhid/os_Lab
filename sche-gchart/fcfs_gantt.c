#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);   // koyta process ache seta input newa hocche

    int bt[n], wt[n], tat[n];   // bt = burst time, wt = waiting time, tat = turnaround time

    printf("Enter burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);   // prottek process er burst time input newa hocche
    }

    wt[0] = 0; // first process ke wait korte hoy na, tai 0

    // FCFS mane process gulo je order e ashe sei order e chole
    // tai age er process er waiting time + burst time = porer process er waiting time
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];   // turnaround time = waiting time + burst time
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    // average ber kora hocche
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    // ------- Gantt Chart -------
    // upor er sarigulo | P1 | P2 | P3 | ei rokom kore print hoy
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) printf("_____");
    printf("\n|");
    for (int i = 0; i < n; i++) printf(" P%d  |", i + 1);
    printf("\n ");
    for (int i = 0; i < n; i++) printf("_____");
    printf("\n");

    // niche time gulo print hoy, prottek process shuru o shesh hoyar shomoy
    printf("0");
    for (int i = 0; i < n; i++) {
        printf("%5d", tat[i]);
    }
    printf("\n");

    return 0;
}
