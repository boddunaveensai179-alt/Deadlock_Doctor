#include <stdio.h>
#include "memory.h"
#include "avoidance.h"
#include "deadlock.h"
#include "filesystem.h"
#include "resource.h"
#include "sync.h"
void display_main_menu()
{
    printf("\n");
    printf("============================================\n");
    printf("              DEADLOCK DOCTOR\n");
    printf("============================================\n");
    printf("       Linux Resource Management System\n");
    printf("============================================\n");

    printf("\n1.  Process Manager\n");
    printf("2.  IPC Manager\n");
    printf("3.  Resource Manager\n");
    printf("4.  Memory Manager\n");
    printf("5.  File Manager\n");
    printf("6.  Synchronization Manager\n");
    printf("7.  Deadlock Detection\n");
    printf("8.  Deadlock Avoidance\n");
    printf("9.  Exit\n");

    printf("\nEnter choice: ");
}


void memory_menu()
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("============================================\n");
        printf("             MEMORY MANAGER\n");
        printf("============================================\n");

        printf("1. Process Memory Layout\n");
        printf("2. Dynamic Memory Allocation\n");
        printf("3. Copy-on-Write\n");
        printf("4. Memory Error Handling\n");
        printf("5. Demand Paging\n");
        printf("6. Memory Debugging\n");
        printf("7. Back to Main Menu\n");

        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n')
                ;

            continue;
        }

        switch (choice)
        {
            case 1:
                show_memory_layout();
                break;

            case 2:
                dynamic_memory_demo();
                break;

            case 3:
                copy_on_write_demo();
                break;

            case 4:
                memory_error_demo();
                break;

            case 5:
                demand_paging_demo();
                break;

            case 6:
                memory_debug_demo();
                break;

            case 7:
    deadlock_detection();
    break;
            default:
                printf("\nInvalid choice. Try again.\n");
        }
    }
}


int main()
{
    int choice;

    while (1)
    {
        display_main_menu();

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");

            while (getchar() != '\n')
                ;

            continue;
        }

        switch (choice)
        {
            /*
             * CO2
             * Process Management
             */
            case 1:

                printf("\n");
                printf("============================================\n");
                printf("             PROCESS MANAGER\n");
                printf("============================================\n");

                printf("Process Manager module is active.\n");
                printf("CO2: Process creation, execution,\n");
                printf("synchronization and termination.\n");

                break;


            /*
             * CO3
             * Inter-Process Communication
             */
            case 2:

                printf("\n");
                printf("============================================\n");
                printf("               IPC MANAGER\n");
                printf("============================================\n");

                printf("IPC Manager module is active.\n");
                printf("CO3: Pipes, FIFOs, signals and\n");
                printf("asynchronous process notifications.\n");

                break;


            /*
             * Resource Management
             */
         case 3:

    printf("\n");
    printf("========================================\n");
    printf("          RESOURCE MANAGER\n");
    printf("========================================\n");

    resource_manager_demo();

    break;
            /*
             * CO4
             * Memory Management
             */
            case 4:

                memory_menu();

                break;


            /*
             * CO5
             * File Systems
             */
          case 5:
{
    int file_choice;

    while (1)
    {
        printf("\n");
        printf("============================================\n");
        printf("              FILE MANAGER\n");
        printf("============================================\n");

        printf("1. Create File\n");
        printf("2. Read / Write File\n");
        printf("3. File Descriptor Demo\n");
        printf("4. Buffered I/O\n");
        printf("5. Unbuffered I/O\n");
        printf("6. Memory-Mapped File I/O\n");
        printf("7. Directory Demo\n");
        printf("8. File System Information\n");
        printf("9. Back to Main Menu\n");

        printf("\nEnter choice: ");

        if (scanf("%d", &file_choice) != 1)
        {
            printf("Invalid input.\n");

            while (getchar() != '\n')
                ;

            continue;
        }

        switch (file_choice)
        {
            case 1:
                file_create_demo();
                break;

            case 2:
                file_read_write_demo();
                break;

            case 3:
                file_descriptor_demo();
                break;

            case 4:
                buffered_io_demo();
                break;

            case 5:
                unbuffered_io_demo();
                break;

            case 6:
                mmap_file_demo();
                break;

            case 7:
                directory_demo();
                break;

            case 8:
                filesystem_debug_demo();
                break;

            case 9:
                break;

            default:
                printf("Invalid choice.\n");
        }

        if (file_choice == 9)
            break;
    }

    break;
}

        case 6:
{
    int sync_choice;

    while (1)
    {
        printf("\n");
        printf("============================================\n");
        printf("       SYNCHRONIZATION MANAGER\n");
        printf("============================================\n");

        printf("1. POSIX Threads\n");
        printf("2. Race Condition\n");
        printf("3. Mutex Synchronization\n");
        printf("4. Condition Variables\n");
        printf("5. Counting Semaphores\n");
        printf("6. Deadlock / Concurrency Hazard\n");
        printf("7. Back to Main Menu\n");

        printf("\nEnter choice: ");

        if (scanf("%d", &sync_choice) != 1)
        {
            printf("Invalid input.\n");

            while (getchar() != '\n')
                ;

            continue;
        }

        switch (sync_choice)
        {
            case 1:
                thread_demo();
                break;

            case 2:
                race_condition_demo();
                break;

            case 3:
                mutex_demo();
                break;

            case 4:
                condition_variable_demo();
                break;

            case 5:
                semaphore_demo();
                break;

            case 6:
                deadlock_demo();
                break;

            case 7:
                break;

            default:
                printf("Invalid choice.\n");
        }

        if (sync_choice == 7)
            break;
    }

    break;
}

            /*
             * Deadlock Detection
             */
            case 7:
    deadlock_detection();
    break;

            /*
             * Deadlock Avoidance
             */
            case 8:
    deadlock_avoidance();
    break;
            /*
             * Exit
             */
            case 9:

                printf("\n");
                printf("============================================\n");
                printf("        Exiting Deadlock Doctor...\n");
                printf("============================================\n");

                return 0;


            default:

                printf("\nInvalid choice. Please select 1-9.\n");
        }
    }

    return 0;
}
