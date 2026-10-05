#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <limits.h>
#include <stdlib.h>

#include "../include/system.h"

void show_system_information(void)
{
    struct utsname system_info;
    char cwd[PATH_MAX];

    printf("\n========================================\n");
    printf("        CO1 - SYSTEM INFORMATION\n");
    printf("========================================\n");

    /* Linux system information */
    if (uname(&system_info) == 0)
    {
        printf("Operating System : %s\n", system_info.sysname);
        printf("Kernel Release   : %s\n", system_info.release);
        printf("Kernel Version   : %s\n", system_info.version);
        printf("Machine          : %s\n", system_info.machine);
    }

    /* Process information */
    printf("\n--- Process Information ---\n");

    printf("Process ID       : %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());

    /* User information */
    printf("\n--- User Information ---\n");

    printf("User ID          : %d\n", getuid());
    printf("Group ID         : %d\n", getgid());

    /* Current working directory */
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("\nCurrent Directory: %s\n", cwd);
    }

    /* Shell information */
    char *shell = getenv("SHELL");

    if (shell != NULL)
    {
        printf("Shell            : %s\n", shell);
    }

    /* Direct Linux system call */
    printf("\n--- System Call Demonstration ---\n");

    long pid_from_syscall = syscall(SYS_getpid);

    printf("PID using syscall(): %ld\n", pid_from_syscall);

    printf("\nThis program is running in User Space.\n");
    printf("It requests services from the Linux kernel using system calls.\n");

    printf("========================================\n");
}
