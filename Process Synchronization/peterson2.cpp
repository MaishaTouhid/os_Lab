#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int flag[2];
int turn;
int counter = 0;
void enter_critical_section(int process_id)
{
    int other = 1 - process_id;

    flag[process_id] = 1;
    turn = other;

    while (flag[other] == 1 && turn == other)
    {
        // busy waiting
    }
}

void leave_critical_section(int process_id)
{
    flag[process_id] = 0;
}

void *process_function(void *arg)
{
    int process_id = *(int *)arg;

    for (int i = 0; i < 5; i++)
    {
        enter_critical_section(process_id);

        printf("Process %d is in critical section, counter = %d\n", process_id, counter);
        counter++;
        sleep(1);

        leave_critical_section(process_id);

        printf("Process %d is in remainder section\n", process_id);
    }

    return NULL;
}

int main()
{
    pthread_t t0, t1;
    int id0 = 0, id1 = 1;

    flag[0] = flag[1] = 0;
    turn = 0;

    pthread_create(&t0, NULL, process_function, &id0);
    pthread_create(&t1, NULL, process_function, &id1);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("Final counter value = %d\n", counter);
    return 0;
}