#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n], id[n];   // id = original process number, sort er por o mone rakhar jonno

    printf("Enter burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        id[i] = i + 1;   // shuru te process number mile thake
    }

    // Bubble sort diye burst time gulo choto theke boro sajano hocche
    // shathe shathe id[] o swap kora hocche, jate bujha jay kon process ta ki
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                int temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = id[j];
                id[j] = id[j + 1];
                id[j + 1] = temp;
            }
        }
    }

    wt[0] = 0; // sort er por sobcheye choto burst time wala process ke wait korte hoy na

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    float totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\n", id[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    // ------- Gantt Chart -------
    // execution order ekhon sorted order onujayi, tai id[] use kora hocche
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
