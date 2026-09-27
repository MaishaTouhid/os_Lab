
#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n], rt[n], wt[n], tat[n];

    // Gantt Chart arrays
    int ganttProcess[100];
    int ganttStart[100];
    int ganttEnd[100];
    int ganttCount = 0;

    printf("Enter arrival time, burst time and priority:\n");

    for (int i = 0; i < n; i++) {
        printf("P%d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);

        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);

        printf("P%d - Priority: ", i + 1);
        scanf("%d", &pr[i]);

        rt[i] = bt[i];
    }

    int time = 0;
    int done = 0;

    // Preemptive Priority Scheduling
    while (done < n) {

        int idx = -1;
        int highestPriority = 9999;

        for (int i = 0; i < n; i++) {

            if (at[i] <= time &&
                rt[i] > 0 &&
                pr[i] < highestPriority) {

                highestPriority = pr[i];
                idx = i;
            }
        }

        // If no process has arrived
        if (idx == -1) {
            time++;
            continue;
        }

        int startTime = time;

        rt[idx]--;
        time++;

        // Gantt Chart
        // If same process continues, extend its previous block
        if (ganttCount > 0 &&
            ganttProcess[ganttCount - 1] == idx + 1) {

            ganttEnd[ganttCount - 1] = time;
        }
        else {
            ganttProcess[ganttCount] = idx + 1;
            ganttStart[ganttCount] = startTime;
            ganttEnd[ganttCount] = time;
            ganttCount++;
        }

        // Process completed
        if (rt[idx] == 0) {
            tat[idx] = time - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            done++;
        }
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n");

    for (int i = 0; i < ganttCount; i++) {
        printf("| P%d ", ganttProcess[i]);
    }
    printf("|\n");

    printf("%d", ganttStart[0]);

    for (int i = 0; i < ganttCount; i++) {
        printf("    %d", ganttEnd[i]);
    }

    printf("\n");

    float totalWT = 0, totalTAT = 0;

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {

        totalWT += wt[i];
        totalTAT += tat[i];

        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               pr[i],
               wt[i],
               tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n",
           totalWT / n);

    printf("Average Turnaround Time = %.2f\n",
           totalTAT / n);

    return 0;
}

