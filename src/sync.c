#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include "sync.h"

int shared_counter = 0;

pthread_mutex_t counter_mutex;


/* ================================
   THREAD FUNCTION
   ================================ */

void *thread_function(void *arg)
{
    int id = *(int *)arg;

    printf("Thread %d is running.\n", id);

    sleep(1);

    printf("Thread %d completed.\n", id);

    return NULL;
}


/* ================================
   POSIX THREAD DEMO
   ================================ */

void thread_demo()
{
    printf("\n====================================\n");
    printf("          POSIX THREAD DEMO\n");
    printf("====================================\n");

    pthread_t threads[2];

    int ids[2] = {1, 2};

    for (int i = 0; i < 2; i++)
    {
        if (pthread_create(&threads[i],
                           NULL,
                           thread_function,
                           &ids[i]) != 0)
        {
            perror("pthread_create");
            return;
        }
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");
}


/* ================================
   RACE CONDITION
   ================================ */

void *race_worker(void *arg)
{
    for (int i = 0; i < 100000; i++)
    {
        shared_counter++;
    }

    return NULL;
}


void race_condition_demo()
{
    printf("\n====================================\n");
    printf("          RACE CONDITION DEMO\n");
    printf("====================================\n");

    shared_counter = 0;

    pthread_t t1, t2;

    pthread_create(&t1, NULL, race_worker, NULL);
    pthread_create(&t2, NULL, race_worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Expected counter value : 200000\n");
    printf("Actual counter value   : %d\n", shared_counter);

    printf("\nMultiple threads accessed shared data\n");
    printf("without synchronization.\n");
}


/* ================================
   MUTEX
   ================================ */

void *mutex_worker(void *arg)
{
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&counter_mutex);

        shared_counter++;

        pthread_mutex_unlock(&counter_mutex);
    }

    return NULL;
}


void mutex_demo()
{
    printf("\n====================================\n");
    printf("             MUTEX DEMO\n");
    printf("====================================\n");

    shared_counter = 0;

    pthread_t t1, t2;

    pthread_mutex_init(&counter_mutex, NULL);

    pthread_create(&t1, NULL, mutex_worker, NULL);
    pthread_create(&t2, NULL, mutex_worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Expected counter value : 200000\n");
    printf("Actual counter value   : %d\n", shared_counter);

    pthread_mutex_destroy(&counter_mutex);

    printf("\nMutex protected the shared resource.\n");
}


/* ================================
   CONDITION VARIABLE
   ================================ */

pthread_mutex_t condition_mutex;
pthread_cond_t condition_variable;

int data_ready = 0;


void *consumer_thread(void *arg)
{
    pthread_mutex_lock(&condition_mutex);

    while (!data_ready)
    {
        printf("Consumer waiting for data...\n");

        pthread_cond_wait(&condition_variable,
                          &condition_mutex);
    }

    printf("Consumer received data.\n");

    pthread_mutex_unlock(&condition_mutex);

    return NULL;
}


void *producer_thread(void *arg)
{
    sleep(2);

    pthread_mutex_lock(&condition_mutex);

    data_ready = 1;

    printf("Producer generated data.\n");

    pthread_cond_signal(&condition_variable);

    pthread_mutex_unlock(&condition_mutex);

    return NULL;
}


void condition_variable_demo()
{
    printf("\n====================================\n");
    printf("       CONDITION VARIABLE DEMO\n");
    printf("====================================\n");

    pthread_t producer;
    pthread_t consumer;

    pthread_mutex_init(&condition_mutex, NULL);

    pthread_cond_init(&condition_variable, NULL);

    data_ready = 0;

    pthread_create(&consumer,
                   NULL,
                   consumer_thread,
                   NULL);

    pthread_create(&producer,
                   NULL,
                   producer_thread,
                   NULL);

    pthread_join(consumer, NULL);
    pthread_join(producer, NULL);

    pthread_mutex_destroy(&condition_mutex);

    pthread_cond_destroy(&condition_variable);

    printf("Thread coordination completed.\n");
}


/* ================================
   COUNTING SEMAPHORE
   ================================ */

sem_t resource_semaphore;


void *semaphore_worker(void *arg)
{
    int id = *(int *)arg;

    printf("Thread %d waiting for resource...\n", id);

    sem_wait(&resource_semaphore);

    printf("Thread %d acquired resource.\n", id);

    sleep(1);

    printf("Thread %d releasing resource.\n", id);

    sem_post(&resource_semaphore);

    return NULL;
}


void semaphore_demo()
{
    printf("\n====================================\n");
    printf("        COUNTING SEMAPHORE DEMO\n");
    printf("====================================\n");

    pthread_t threads[4];

    int ids[4] = {1, 2, 3, 4};

    /*
       Only two threads can use the
       resource simultaneously.
    */

    sem_init(&resource_semaphore, 0, 2);

    for (int i = 0; i < 4; i++)
    {
        pthread_create(&threads[i],
                       NULL,
                       semaphore_worker,
                       &ids[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&resource_semaphore);

    printf("Semaphore demonstration completed.\n");
}


/* ================================
   DEADLOCK DEMO
   ================================ */

pthread_mutex_t resource1;
pthread_mutex_t resource2;


void *deadlock_thread1(void *arg)
{
    printf("Thread 1 locking Resource 1...\n");

    pthread_mutex_lock(&resource1);

    sleep(1);

    printf("Thread 1 waiting for Resource 2...\n");

    pthread_mutex_lock(&resource2);

    pthread_mutex_unlock(&resource2);
    pthread_mutex_unlock(&resource1);

    return NULL;
}


void *deadlock_thread2(void *arg)
{
    printf("Thread 2 locking Resource 2...\n");

    pthread_mutex_lock(&resource2);

    sleep(1);

    printf("Thread 2 waiting for Resource 1...\n");

    pthread_mutex_lock(&resource1);

    pthread_mutex_unlock(&resource1);
    pthread_mutex_unlock(&resource2);

    return NULL;
}


void deadlock_demo()
{
    printf("\n====================================\n");
    printf("           DEADLOCK DEMO\n");
    printf("====================================\n");

    printf("\nThis demonstration shows the deadlock condition:\n");

    printf("Thread 1 -> holds Resource 1 -> waits for Resource 2\n");
    printf("Thread 2 -> holds Resource 2 -> waits for Resource 1\n");

    printf("\nDo NOT execute the actual circular lock sequence\n");
    printf("inside the main program because it would hang.\n");

    printf("\nDeadlock conditions:\n");

    printf("1. Mutual Exclusion\n");
    printf("2. Hold and Wait\n");
    printf("3. No Preemption\n");
    printf("4. Circular Wait\n");

    printf("\nDeadlock hazard identified successfully.\n");
}
