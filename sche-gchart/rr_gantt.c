#include <stdio.h>

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], wt[n], tat[n];   // rt = remaining time (koto burst time baki ache)

    printf("Enter burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i]; // shuru te remaining time = full burst time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);   // ekbar e ekta process max koto shomoy chalbe

    int time = 0;    // total shomoy koto hoyeche seta track kora hocche
    int done = 0;     // koyta process complete hoyeche

    // ------- Gantt Chart er jonno arrays -------
    // prottibar je process chole tar id ar shesh shomoy save kora hocche
    int ganttProcess[1000], ganttTime[1000], g = 0;

    // jotokkhon na shob process complete hoy totokkhon loop cholbe
    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {   // ei process ta baki thakle
                if (rt[i] > quantum) {
                    // quantum er cheye beshi baki thakle, quantum shomoy chole tarpor next process e jabe
                    time += quantum;
                    rt[i] -= quantum;
                } else {
                    // quantum er theke kom baki thakle, ei process ei shesh hoye jabe
                    time += rt[i];
                    wt[i] = time - bt[i];   // waiting time ber kora hocche
                    rt[i] = 0;
                    done++;   // ekta process complete holo
                }
                // ei execution ta gantt chart e save kora hocche
                ganttProcess[g] = i + 1;
                ganttTime[g] = time;
                g++;
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

    // ------- Gantt Chart -------
    // quantum onujayi bar bar ekই process asha shovabik, tai shob segment e dekhano hocche
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < g; i++) printf("_____");
    printf("\n|");
    for (int i = 0; i < g; i++) printf(" P%d  |", ganttProcess[i]);
    printf("\n ");
    for (int i = 0; i < g; i++) printf("_____");
    printf("\n");

    printf("0");
    for (int i = 0; i < g; i++) {
        printf("%5d", ganttTime[i]);
    }
    printf("\n");

    return 0;
}
