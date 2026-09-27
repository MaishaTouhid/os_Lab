#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int flag[2];        // দুইটা process এর flag
int turn;            // কার পালা
int counter = 0;     // shared resource (critical section এ এটাই modify হবে)

void enter_critical_section(int process_id) {
    int other = 1 - process_id;   // অন্য process এর id

    flag[process_id] = 1;         // আমি ঢুকতে চাই
    turn = other;                 // অন্যকে পালা দিলাম

    // wait until it's safe to enter
    while (flag[other] == 1 && turn == other) {
        // busy waiting
    }
}

void leave_critical_section(int process_id) {
    flag[process_id] = 0;         // আমার আর দরকার নেই
}

void* process_function(void* arg) {
    int process_id = *(int*)arg;

    for (int i = 0; i < 5; i++) {
        enter_critical_section(process_id);

        // ---- Critical Section শুরু ----
        printf("Process %d is in critical section, counter = %d\n", process_id, counter);
        counter++;
        sleep(1);   // simulate some work
        // ---- Critical Section শেষ ----

        leave_critical_section(process_id);

        // remainder section (critical section এর বাইরের কাজ)
        printf("Process %d is in remainder section\n", process_id);
    }

    return NULL;
}

int main() {
    pthread_t t0, t1;
    int id0 = 0, id1 = 1;

    flag[0] = flag[1] = 0;
    turn = 0;

    // দুইটা "process" (thread হিসেবে) তৈরি করা হলো
    pthread_create(&t0, NULL, process_function, &id0);
    pthread_create(&t1, NULL, process_function, &id1);

    // দুইটা শেষ হওয়ার জন্য wait
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("Final counter value = %d\n", counter);
    return 0;
}