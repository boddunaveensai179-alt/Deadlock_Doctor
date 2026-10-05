#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#include "../include/process.h"

static void create_process(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /* Child process */
        printf("\n[CHILD]\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("Child process is running...\n");

        sleep(3);

        printf("Child process completed.\n");

        exit(0);
    }

    /* Parent process */
    printf("\n[PARENT]\n");
    printf("Parent PID : %d\n", getpid());
    printf("Created Child PID : %d\n", pid);

    printf("Waiting for child process...\n");

    if (waitpid(pid, NULL, 0) == -1)
    {
        perror("waitpid");
        return;
    }

    printf("Child process terminated.\n");
}

static void execute_process(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        printf("\n[CHILD]\n");
        printf("PID: %d\n", getpid());
        printf("Executing 'ls -l' using exec().\n\n");

        execlp("ls", "ls", "-l", NULL);

        /* exec only returns when an error occurs */
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    printf("\n[PARENT]\n");
    printf("Created child PID: %d\n", pid);

    waitpid(pid, NULL, 0);

    printf("\nChild execution completed.\n");
}

static void show_process_status(void)
{
    pid_t pid;

    printf("\nEnter PID to check: ");

    if (scanf("%d", &pid) != 1)
    {
        printf("Invalid PID.\n");
        return;
    }

    errno = 0;

    if (kill(pid, 0) == 0)
    {
        printf("Process %d is currently existing.\n", pid);
    }
    else
    {
        if (errno == ESRCH)
        {
            printf("Process %d does not exist.\n", pid);
        }
        else if (errno == EPERM)
        {
            printf("Process %d exists, but permission is denied.\n", pid);
        }
        else
        {
            perror("kill");
        }
    }
}

static void terminate_process(void)
{
    pid_t pid;

    printf("\nEnter PID to terminate: ");

    if (scanf("%d", &pid) != 1)
    {
        printf("Invalid PID.\n");
        return;
    }

    if (kill(pid, SIGTERM) == 0)
    {
        printf("SIGTERM sent to process %d.\n", pid);
    }
    else
    {
        perror("kill");
    }
}

static void process_information(void)
{
    printf("\n========================================\n");
    printf("       CURRENT PROCESS INFORMATION\n");
    printf("========================================\n");

    printf("Current PID        : %d\n", getpid());
    printf("Parent PID         : %d\n", getppid());
    printf("User ID            : %d\n", getuid());
    printf("Group ID           : %d\n", getgid());

    printf("========================================\n");
}

void process_manager(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("          PROCESS MANAGER\n");
        printf("========================================\n");
        printf("1. Create Child Process\n");
        printf("2. Execute Program using exec()\n");
        printf("3. Check Process Status\n");
        printf("4. Terminate Process\n");
        printf("5. Current Process Information\n");
        printf("6. Back to Main Menu\n");
        printf("----------------------------------------\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            return;
        }

        switch (choice)
        {
            case 1:
                create_process();
                break;

            case 2:
                execute_process();
                break;

            case 3:
                show_process_status();
                break;

            case 4:
                terminate_process();
                break;

            case 5:
                process_information();
                break;

            case 6:
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}
