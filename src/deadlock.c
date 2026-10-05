#include <stdio.h>
#include <stdlib.h>

#include "deadlock.h"

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10


void deadlock_detection()
{
    int processes;
    int resources;

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int request[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];

    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];

    printf("\n============================================\n");
    printf("          DEADLOCK DETECTION\n");
    printf("============================================\n");

    printf("\nEnter number of processes (1-%d): ",
           MAX_PROCESSES);

    scanf("%d", &processes);

    printf("Enter number of resources (1-%d): ",
           MAX_RESOURCES);

    scanf("%d", &resources);

    if (processes <= 0 || processes > MAX_PROCESSES ||
        resources <= 0 || resources > MAX_RESOURCES)
    {
        printf("\nInvalid number of processes/resources.\n");
        return;
    }


    /* ================================
       AVAILABLE RESOURCES
       ================================ */

    printf("\nEnter Available Resource Vector:\n");

    for (int j = 0; j < resources; j++)
    {
        printf("Available R%d: ", j);
        scanf("%d", &available[j]);

        work[j] = available[j];
    }


    /* ================================
       ALLOCATION MATRIX
       ================================ */

    printf("\nEnter Allocation Matrix\n");
    printf("(Resources currently allocated to each process)\n");

    for (int i = 0; i < processes; i++)
    {
        printf("\nProcess P%d:\n", i);

        for (int j = 0; j < resources; j++)
        {
            printf("Allocated R%d: ", j);
            scanf("%d", &allocation[i][j]);
        }
    }


    /* ================================
       REQUEST MATRIX
       ================================ */

    printf("\nEnter Request Matrix\n");
    printf("(Additional resources required by each process)\n");

    for (int i = 0; i < processes; i++)
    {
        printf("\nProcess P%d:\n", i);

        for (int j = 0; j < resources; j++)
        {
            printf("Requested R%d: ", j);
            scanf("%d", &request[i][j]);
        }
    }


    /* ================================
       INITIALIZE PROCESS STATE
       ================================ */

    for (int i = 0; i < processes; i++)
    {
        finish[i] = 0;
    }


    /* ================================
       DEADLOCK DETECTION
       ================================ */

    int progress;

    do
    {
        progress = 0;

        for (int i = 0; i < processes; i++)
        {
            if (finish[i])
                continue;

            int can_finish = 1;

            for (int j = 0; j < resources; j++)
            {
                if (request[i][j] > work[j])
                {
                    can_finish = 0;
                    break;
                }
            }

            if (can_finish)
            {
                printf("\nP%d can obtain its requested resources.",
                       i);

                printf("\nP%d completes and releases:",
                       i);

                for (int j = 0; j < resources; j++)
                {
                    work[j] += allocation[i][j];

                    printf(" R%d=%d",
                           j,
                           allocation[i][j]);
                }

                printf("\n");

                finish[i] = 1;
                progress = 1;
            }
        }

    } while (progress);


    /* ================================
       DISPLAY FINAL AVAILABLE RESOURCES
       ================================ */

    printf("\n============================================\n");
    printf("           DETECTION RESULT\n");
    printf("============================================\n");

    printf("\nFinal Work Vector: ");

    for (int j = 0; j < resources; j++)
    {
        printf("%d ", work[j]);
    }

    printf("\n");


    /* ================================
       CHECK DEADLOCK
       ================================ */

    int deadlock_found = 0;

    for (int i = 0; i < processes; i++)
    {
        if (!finish[i])
        {
            deadlock_found = 1;
        }
    }


    if (deadlock_found)
    {
        printf("\nSTATUS: DEADLOCK DETECTED\n");

        printf("\nProcesses involved:\n");

        for (int i = 0; i < processes; i++)
        {
            if (!finish[i])
            {
                printf("P%d ", i);
            }
        }

        printf("\n");

        printf("\nThese processes cannot complete because");
        printf(" their requested resources cannot");
        printf(" currently be satisfied.\n");
    }
    else
    {
        printf("\nSTATUS: NO DEADLOCK\n");

        printf("\nAll processes can eventually complete.\n");
    }

    printf("\n============================================\n");
}
