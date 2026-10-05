#include <stdio.h>
#include "resource.h"

#define MAX_RESOURCES 5
#define MAX_PROCESSES 5

void resource_manager_demo()
{
    int resources[MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];

    int n, i, j;
    int process, resource, amount;

    printf("\n========================================\n");
    printf("          RESOURCE MANAGER\n");
    printf("========================================\n");

    printf("Enter number of resources (1-%d): ", MAX_RESOURCES);
    scanf("%d", &n);

    if (n < 1 || n > MAX_RESOURCES)
    {
        printf("Invalid number of resources.\n");
        return;
    }

    /* Initialize resources */
    for (i = 0; i < n; i++)
    {
        printf("Enter total instances of Resource R%d: ", i);
        scanf("%d", &resources[i]);

        available[i] = resources[i];
    }

    /* Initialize allocation matrix */
    for (i = 0; i < MAX_PROCESSES; i++)
    {
        for (j = 0; j < MAX_RESOURCES; j++)
        {
            allocation[i][j] = 0;
        }
    }

    while (1)
    {
        printf("\n========================================\n");
        printf("          RESOURCE MANAGER\n");
        printf("========================================\n");

        printf("1. Display Resources\n");
        printf("2. Allocate Resource\n");
        printf("3. Release Resource\n");
        printf("4. Display Allocation\n");
        printf("5. Back to Main Menu\n");

        printf("\nEnter choice: ");
        scanf("%d", &i);

        if (i == 1)
        {
            printf("\nResource Status:\n");

            for (j = 0; j < n; j++)
            {
                printf("R%d: Total = %d, Available = %d\n",
                       j, resources[j], available[j]);
            }
        }

        else if (i == 2)
        {
            printf("\nEnter process number (0-%d): ", MAX_PROCESSES - 1);
            scanf("%d", &process);

            printf("Enter resource number (0-%d): ", n - 1);
            scanf("%d", &resource);

            printf("Enter amount: ");
            scanf("%d", &amount);

            if (process < 0 || process >= MAX_PROCESSES ||
                resource < 0 || resource >= n ||
                amount <= 0)
            {
                printf("Invalid input.\n");
                continue;
            }

            if (amount <= available[resource])
            {
                available[resource] -= amount;
                allocation[process][resource] += amount;

                printf("Resource allocated successfully.\n");
            }
            else
            {
                printf("Resource unavailable.\n");
                printf("Process must wait.\n");
            }
        }

        else if (i == 3)
        {
            printf("\nEnter process number (0-%d): ", MAX_PROCESSES - 1);
            scanf("%d", &process);

            printf("Enter resource number (0-%d): ", n - 1);
            scanf("%d", &resource);

            printf("Enter amount: ");
            scanf("%d", &amount);

            if (process < 0 || process >= MAX_PROCESSES ||
                resource < 0 || resource >= n ||
                amount <= 0)
            {
                printf("Invalid input.\n");
                continue;
            }

            if (amount <= allocation[process][resource])
            {
                allocation[process][resource] -= amount;
                available[resource] += amount;

                printf("Resource released successfully.\n");
            }
            else
            {
                printf("Release denied.\n");
                printf("Process does not hold enough resources.\n");
            }
        }

        else if (i == 4)
        {
            printf("\n========================================\n");
            printf("       CURRENT RESOURCE ALLOCATION\n");
            printf("========================================\n");

            printf("       ");

            for (j = 0; j < n; j++)
                printf("R%d ", j);

            printf("\n");

            for (process = 0; process < MAX_PROCESSES; process++)
            {
                printf("P%d     ", process);

                for (j = 0; j < n; j++)
                {
                    printf("%d  ", allocation[process][j]);
                }

                printf("\n");
            }
        }

        else if (i == 5)
        {
            break;
        }

        else
        {
            printf("Invalid choice.\n");
        }
    }
}
