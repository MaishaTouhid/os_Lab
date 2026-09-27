#include <stdio.h>

void roundRobin(int bt[], int n, int quantum);
void fcfs(int bt[], int n);

int main() {
    int n1, n2;

    printf("Enter number of processes in Queue 1: ");
    scanf("%d", &n1);

    int bt1[n1];

    printf("Enter burst time of Queue 1 processes:\n");
    for (int i = 0; i < n1; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt1[i]);
    }

    printf("\nEnter number of processes in Queue 2: ");
    scanf("%d", &n2);

    int bt2[n2];

    printf("Enter burst time of Queue 2 processes:\n");
    for (int i = 0; i < n2; i++) {
        printf("P%d: ", i + n1 + 1);
        scanf("%d", &bt2[i]);
    }

    int quantum = 2;

    printf("\n--- Queue 1 (Round Robin) ---\n");
    roundRobin(bt1, n1, quantum);

    printf("\n--- Queue 2 (FCFS) ---\n");
    fcfs(bt2, n2);

    return 0;
}


// Queue 1: Round Robin
void roundRobin(int bt[], int n, int quantum) {

    int rt[n], wt[n], tat[n];

    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
        wt[i] = 0;
    }

    int time = 0;
    int done = 0;

    while (done < n) {

        for (int i = 0; i < n; i++) {

            if (rt[i] > 0) {

                if (rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                }
                else {
                    time += rt[i];
                    rt[i] = 0;

                    tat[i] = time;
                    wt[i] = tat[i] - bt[i];

                    done++;
                }
            }
        }
    }

    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {

        totalWT += wt[i];
        totalTAT += tat[i];

        printf("P%d\t%d\t%d\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n",
           totalWT / n);

    printf("Average Turnaround Time = %.2f\n",
           totalTAT / n);
}


// Queue 2: FCFS
void fcfs(int bt[], int n) {

    int wt[n], tat[n];

    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    int time = 0;

    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");

    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < n; i++) {

        time += bt[i];
        tat[i] = wt[i] + bt[i];

        totalWT += wt[i];
        totalTAT += tat[i];

        printf("P%d\t%d\t%d\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n",
           totalWT / n);

    printf("Average Turnaround Time = %.2f\n",
           totalTAT / n);
}