#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], pr[n], wt[n], tat[n], id[n];   // id = original process number

    printf("Enter burst time and priority of each process (lower number = higher priority):\n");
    for (int i = 0; i < n; i++) {
        printf("P%d - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P%d - Priority: ", i + 1);
        scanf("%d", &pr[i]);
        id[i] = i + 1;   // shuru te process number mile thake
    }

    // Bubble sort diye priority onujayi sajano hocche
    // choto priority number thakle sei process age chole
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pr[j] > pr[j + 1]) {
                int temp = pr[j];
                pr[j] = pr[j + 1];
                pr[j + 1] = temp;

                // priority er sathe sathe burst time o id o swap kora hocche
                // noile process gulo mismatch hoye jabe
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }

    wt[0] = 0; // sorted list e prothom process ke wait korte hoy na

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];   // age er process gulo shesh hote koto shomoy laglo
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t\t%d\t%d\n", id[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    // ------- Gantt Chart -------
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) printf("_____");
    printf("\n|");
    for (int i = 0; i < n; i++) printf(" P%d  |", id[i]);
    printf("\n ");
    for (int i = 0; i < n; i++) printf("_____");
    printf("\n");

    printf("0");
    for (int i = 0; i < n; i++) {
        printf("%5d", tat[i]);
    }
    printf("\n");

    return 0;
}
