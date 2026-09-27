#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], wt[n], tat[n];
    int queue[n];

    printf("Enter burst time of processes:\n");

    for (int i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
        queue[i] = 1;   // Initially all processes are in Queue 1
        wt[i] = 0;
    }

    int time = 0;
    int done = 0;

    int q1 = 2;   // Queue 1 quantum
    int q2 = 4;   // Queue 2 quantum

    // Multilevel Feedback Queue Scheduling

    while (done < n) {

        // ---------------- Queue 1: Round Robin ----------------
        for (int i = 0; i < n; i++) {

            if (queue[i] == 1 && rt[i] > 0) {

                if (rt[i] > q1) {
                    time += q1;
                    rt[i] -= q1;

                    // Move to Queue 2
                    queue[i] = 2;
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


        // ---------------- Queue 2: Round Robin ----------------
        for (int i = 0; i < n; i++) {

            if (queue[i] == 2 && rt[i] > 0) {

                if (rt[i] > q2) {
                    time += q2;
                    rt[i] -= q2;

                    // Move to Queue 3
                    queue[i] = 3;
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


        // ---------------- Queue 3: FCFS ----------------
        for (int i = 0; i < n; i++) {

            if (queue[i] == 3 && rt[i] > 0) {

                time += rt[i];
                rt[i] = 0;

                tat[i] = time;
                wt[i] = tat[i] - bt[i];

                done++;
            }
        }
    }


    // ---------------- Display Result ----------------

    float totalWT = 0;
    float totalTAT = 0;

    printf("\nProcess\tBurst\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {

        totalWT += wt[i];
        totalTAT += tat[i];

        printf("P%d\t%d\t%d\t%d\n",
               i + 1,
               bt[i],
               wt[i],
               tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n",
           totalWT / n);

    printf("Average Turnaround Time = %.2f\n",
           totalTAT / n);

    return 0;
}