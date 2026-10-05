#include <stdio.h>
#include "avoidance.h"

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void deadlock_avoidance()
{
    int n, m;

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int maximum[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    int available[MAX_RESOURCES];
    int work[MAX_RESOURCES];

    int finish[MAX_PROCESSES] = {0};
    int safe_sequence[MAX_PROCESSES];

    printf("\n============================================\n");
    printf("          DEADLOCK AVOIDANCE\n");
    printf("          BANKER'S ALGORITHM\n");
    printf("============================================\n");

    printf("\nEnter number of processes (1-%d): ", MAX_PROCESSES);
    scanf("%d", &n);

    printf("Enter number of resources (1-%d): ", MAX_RESOURCES);
    scanf("%d", &m);

    if (n <= 0 || n > MAX_PROCESSES ||
        m <= 0 || m > MAX_RESOURCES)
    {
        printf("\nInvalid input.\n");
        return;
    }

    /* Available resources */
    printf("\nEnter Available Resources:\n");

    for (int j = 0; j < m; j++)
    {
        printf("Available R%d: ", j);
        scanf("%d", &available[j]);
        work[j] = available[j];
    }

    /* Allocation matrix */
    printf("\nEnter Allocation Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    /* Maximum matrix */
    printf("\nEnter Maximum Requirement Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++)
        {
            scanf("%d", &maximum[i][j]);

            if (maximum[i][j] < allocation[i][j])
            {
                printf("\nInvalid input: Maximum cannot be less than Allocation.\n");
                return;
            }

            need[i][j] =
                maximum[i][j] - allocation[i][j];
        }
    }

    /* Display Need Matrix */
    printf("\nNeed Matrix = Maximum - Allocation\n\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (int j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    /* Safety Algorithm */
    int count = 0;
    int found;

    while (count < n)
    {
        found = 0;

        for (int i = 0; i < n; i++)
        {
            if (finish[i])
                continue;

            int possible = 1;

            for (int j = 0; j < m; j++)
            {
                if (need[i][j] > work[j])
                {
                    possible = 0;
                    break;
                }
            }

            if (possible)
            {
                printf("\nP%d can safely execute.", i);

                for (int j = 0; j < m; j++)
                {
                    work[j] += allocation[i][j];
                }

                finish[i] = 1;
                safe_sequence[count] = i;
                count++;
                found = 1;
            }
        }

        if (!found)
            break;
    }

    printf("\n\n============================================\n");
    printf("              SAFETY RESULT\n");
    printf("============================================\n");

    if (count == n)
    {
        printf("\nSTATUS: SAFE STATE\n");

        printf("\nSafe Sequence: ");

        for (int i = 0; i < n; i++)
        {
            printf("P%d", safe_sequence[i]);

            if (i != n - 1)
                printf(" -> ");
        }

        printf("\n");
        printf("\nThe system can safely allocate resources\n");
        printf("without entering a deadlock state.\n");
    }
    else
    {
        printf("\nSTATUS: UNSAFE STATE\n");

        printf("\nNo complete safe sequence exists.\n");
        printf("Resource allocation should be avoided.\n");
    }

    printf("\n============================================\n");
}
