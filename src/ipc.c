#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "../include/ipc.h"

#define FIFO_PATH "data/resource_fifo"

/*
 * Signal handler
 */
static void handle_signal(int signal_number)
{
    if (signal_number == SIGUSR1)
    {
        printf("\n[SIGNAL HANDLER]\n");
        printf("SIGUSR1 received: Resource request notification.\n");
    }
    else if (signal_number == SIGUSR2)
    {
        printf("\n[SIGNAL HANDLER]\n");
        printf("SIGUSR2 received: Resource release notification.\n");
    }
    else if (signal_number == SIGTERM)
    {
        printf("\n[SIGNAL HANDLER]\n");
        printf("SIGTERM received.\n");
    }
}

/*
 * Anonymous pipe demonstration
 */
static void anonymous_pipe_demo(void)
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return;
    }

    if (pid == 0)
    {
        /*
         * Child only reads.
         */
        close(pipe_fd[1]);

        char buffer[100];

        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1);

        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';

            printf("\n[CHILD PROCESS]\n");
            printf("PID: %d\n", getpid());
            printf("Received through pipe: %s\n", buffer);
        }

        close(pipe_fd[0]);

        exit(0);
    }

    /*
     * Parent only writes.
     */
    close(pipe_fd[0]);

    const char *message = "REQUEST R1";

    printf("\n[PARENT PROCESS]\n");
    printf("PID: %d\n", getpid());
    printf("Sending resource request: %s\n", message);

    write(pipe_fd[1], message, strlen(message));

    close(pipe_fd[1]);

    waitpid(pid, NULL, 0);

    printf("Anonymous pipe communication completed.\n");
}

/*
 * Create named pipe
 */
static void create_fifo(void)
{
    if (mkfifo(FIFO_PATH, 0666) == -1)
    {
        if (errno == EEXIST)
        {
            printf("\nFIFO already exists: %s\n", FIFO_PATH);
        }
        else
        {
            perror("mkfifo");
            return;
        }
    }
    else
    {
        printf("\nFIFO created successfully: %s\n", FIFO_PATH);
    }
}

/*
 * FIFO demonstration
 *
 * We use fork() so that one process writes
 * and another process reads.
 */
static void fifo_demo(void)
{
    create_fifo();

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /*
         * Child reads from FIFO.
         */
        sleep(1);

        int fd = open(FIFO_PATH, O_RDONLY);

        if (fd == -1)
        {
            perror("open FIFO");
            exit(EXIT_FAILURE);
        }

        char buffer[100];

        ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';

            printf("\n[FIFO READER]\n");
            printf("PID: %d\n", getpid());
            printf("Received: %s\n", buffer);
        }

        close(fd);

        exit(0);
    }

    /*
     * Parent writes to FIFO.
     */
    int fd = open(FIFO_PATH, O_WRONLY);

    if (fd == -1)
    {
        perror("open FIFO");
        waitpid(pid, NULL, 0);
        return;
    }

    const char *message = "REQUEST R2";

    printf("\n[FIFO WRITER]\n");
    printf("PID: %d\n", getpid());
    printf("Sending: %s\n", message);

    write(fd, message, strlen(message));

    close(fd);

    waitpid(pid, NULL, 0);

    printf("FIFO communication completed.\n");
}

/*
 * Signal demonstration
 */
static void signal_demo(void)
{
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = handle_signal;

    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction SIGUSR1");
        return;
    }

    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        perror("sigaction SIGUSR2");
        return;
    }

    if (sigaction(SIGTERM, &sa, NULL) == -1)
    {
        perror("sigaction SIGTERM");
        return;
    }

    printf("\n========================================\n");
    printf("         SIGNAL DEMONSTRATION\n");
    printf("========================================\n");

    printf("Current PID: %d\n", getpid());

    printf("\nSending SIGUSR1...\n");
    raise(SIGUSR1);

    printf("\nSending SIGUSR2...\n");
    raise(SIGUSR2);

    printf("\nSignal demonstration completed.\n");
}

/*
 * IPC manager menu
 */
void ipc_manager(void)
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("========================================\n");
        printf("             IPC MANAGER\n");
        printf("========================================\n");

        printf("1. Anonymous Pipe\n");
        printf("2. Named Pipe (FIFO)\n");
        printf("3. Signal Handler\n");
        printf("4. Back to Main Menu\n");

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
                anonymous_pipe_demo();
                break;

            case 2:
                fifo_demo();
                break;

            case 3:
                signal_demo();
                break;

            case 4:
                return;

            default:
                printf("Invalid choice.\n");
        }
    }
}
