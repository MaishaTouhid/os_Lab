#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // at = arrival time, bt = burst time, rt = remaining time
    int at[n], bt[n], rt[n], wt[n], tat[n], completed[n];

    printf("Enter arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];       // shuru te remaining time = full burst time
        completed[i] = 0;    // kono process ekhono complete hoy nai
    }

    int time = 0, done = 0;

    // ------- Gantt Chart er jonno array -------
    // prottek 1 unit shomoy e kon process cholche seta save kora hocche
    int ganttSeq[10000], gcount = 0;

    // ei algorithm preemptive, tai ekdom 1 unit shomoy kore kore check kora hocche
    while (done < n) {
        int idx = -1;
        int minRemaining = 9999;   // ekta boro number diye shuru kora hocche

        // je je process eshe geche (arrival time <= current time)
        // tader moddhe je process er remaining time sobcheye kom, take khoja hocche
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < minRemaining) {
                minRemaining = rt[i];
                idx = i;   // ei process ta ekhon shobcheye kom baki
            }
        }

        if (idx == -1) {
            // kono process ekhono ashe nai, tai time forward niye jaowa hocche
            time++;
            continue;
        }

        rt[idx]--;   // pawa process take 1 unit shomoy chalano hocche
        ganttSeq[gcount++] = idx + 1;   // ei 1 unit shomoy e kon process cholchilo seta save
        time++;

        if (rt[idx] == 0) {
            // process ta shesh hoye geche
            completed[idx] = 1;
            done++;
            tat[idx] = time - at[idx];      // turnaround time = finish time - arrival time
            wt[idx] = tat[idx] - bt[idx];   // waiting time = turnaround time - burst time
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

    // ------- Gantt Chart -------
    // preemptive bole 1 unit kore alada segment na dekhiye, ekই process er poropori
    // unit gulo ke ekshathe merge kore choto poriskar chart banano hocche
    printf("\nGantt Chart:\n");

    int mergedProc[10000], mergedStart[10000], mergedEnd[10000], m = 0;
    mergedProc[0] = ganttSeq[0];
    mergedStart[0] = 0;
    for (int i = 1; i < gcount; i++) {
        if (ganttSeq[i] != ganttSeq[i - 1]) {
            // process change hoyeche, tai age er ta shesh kore notun ta shuru
            mergedEnd[m] = i;
            m++;
            mergedProc[m] = ganttSeq[i];
            mergedStart[m] = i;
        }
    }
    mergedEnd[m] = gcount;
    m++;

    printf(" ");
    for (int i = 0; i < m; i++) printf("_____");
    printf("\n|");
    for (int i = 0; i < m; i++) printf(" P%d  |", mergedProc[i]);
    printf("\n ");
    for (int i = 0; i < m; i++) printf("_____");
    printf("\n");

    printf("%d", mergedStart[0]);
    for (int i = 0; i < m; i++) {
        printf("%5d", mergedEnd[i]);
    }
    printf("\n");

    return 0;
}
