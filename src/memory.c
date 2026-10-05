#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#include "memory.h"

int global_initialized = 100;
int global_uninitialized;

void show_memory_layout()
{
    int stack_variable = 10;
    static int static_variable = 20;

    int *heap_variable = malloc(sizeof(int));

    if (heap_variable == NULL) {
        perror("malloc");
        return;
    }

    *heap_variable = 30;

    printf("\n====================================\n");
    printf("       PROCESS MEMORY LAYOUT\n");
    printf("====================================\n");

    printf("Code address       : %p\n",
           (void *)show_memory_layout);

    printf("Global initialized : %p\n",
           (void *)&global_initialized);

    printf("Global uninitialized: %p\n",
           (void *)&global_uninitialized);

    printf("Static variable    : %p\n",
           (void *)&static_variable);

    printf("Heap address       : %p\n",
           (void *)heap_variable);

    printf("Stack address      : %p\n",
           (void *)&stack_variable);

    free(heap_variable);
}


void dynamic_memory_demo()
{
    printf("\n====================================\n");
    printf("       DYNAMIC MEMORY DEMO\n");
    printf("====================================\n");

    int *arr;

    arr = malloc(5 * sizeof(int));

    if (arr == NULL) {
        perror("malloc");
        return;
    }

    printf("Memory allocated using malloc()\n");

    for (int i = 0; i < 5; i++) {
        arr[i] = (i + 1) * 10;
    }

    printf("Initial values:\n");

    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    arr = realloc(arr, 10 * sizeof(int));

    if (arr == NULL) {
        perror("realloc");
        return;
    }

    printf("Memory expanded using realloc()\n");

    for (int i = 5; i < 10; i++) {
        arr[i] = (i + 1) * 10;
    }

    printf("Expanded values:\n");

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    free(arr);

    printf("Memory released using free()\n");
}


void copy_on_write_demo()
{
    printf("\n====================================\n");
    printf("       COPY-ON-WRITE DEMO\n");
    printf("====================================\n");

    int *shared_memory = malloc(sizeof(int));

    if (shared_memory == NULL) {
        perror("malloc");
        return;
    }

    *shared_memory = 100;

    printf("Before fork():\n");
    printf("Parent value = %d\n", *shared_memory);
    printf("Address      = %p\n",
           (void *)shared_memory);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        free(shared_memory);
        return;
    }

    if (pid == 0) {

        printf("\nChild process:\n");
        printf("Child value before modification = %d\n",
               *shared_memory);

        *shared_memory = 200;

        printf("Child value after modification = %d\n",
               *shared_memory);

        printf("Child address = %p\n",
               (void *)shared_memory);

        exit(0);
    }

    waitpid(pid, NULL, 0);

    printf("\nParent process after child modification:\n");
    printf("Parent value = %d\n",
           *shared_memory);

    printf("Parent address = %p\n",
           (void *)shared_memory);

    free(shared_memory);
}


void memory_error_handler(int signal_number)
{
    printf("\nMemory error signal received: %d\n",
           signal_number);

    printf("Operating system detected invalid memory access.\n");
    printf("Program terminates safely.\n");

    exit(EXIT_FAILURE);
}


void memory_error_demo()
{
    printf("\n====================================\n");
    printf("       MEMORY ERROR DEMO\n");
    printf("====================================\n");

    signal(SIGSEGV, memory_error_handler);

    printf("SIGSEGV handler installed.\n");

    printf("This module demonstrates how the OS\n");
    printf("responds to invalid memory access.\n");

    printf("Memory error handling is enabled.\n");
}


void memory_debug_demo()
{
    printf("\n====================================\n");
    printf("       MEMORY DEBUGGING\n");
    printf("====================================\n");

    printf("Current Process ID: %d\n", getpid());

    printf("\nUseful Linux memory analysis commands:\n");

    printf("1. cat /proc/self/maps\n");
    printf("2. pmap %d\n", getpid());
    printf("3. free -h\n");
    printf("4. ps -o pid,vsz,rss,comm -p %d\n", getpid());

    printf("\nThese tools help analyze:\n");
    printf("- Process memory mappings\n");
    printf("- Virtual memory usage\n");
    printf("- Resident memory\n");
    printf("- Heap and stack regions\n");
}
void demand_paging_demo()
{
    printf("\n====================================\n");
    printf("          DEMAND PAGING DEMO\n");
    printf("====================================\n");

    size_t size = 100 * 1024 * 1024;

    char *memory = malloc(size);

    if (memory == NULL)
    {
        perror("malloc");
        return;
    }

    printf("Virtual memory allocated: %zu MB\n",
           size / (1024 * 1024));

    printf("Accessing memory pages...\n");

    for (size_t i = 0; i < size; i += 4096)
    {
        memory[i] = 1;
    }

    printf("Pages accessed successfully.\n");
    printf("Demand paging demonstration completed.\n");

    free(memory);

    printf("Memory released using free().\n");
}
