#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <dirent.h>

#include "filesystem.h"


void file_create_demo()
{
    printf("\n====================================\n");
    printf("          FILE CREATION\n");
    printf("====================================\n");

    FILE *file = fopen("data/resource_log.txt", "w");

    if (file == NULL)
    {
        perror("fopen");
        return;
    }

    fprintf(file, "DeadlockDoctor Resource Log\n");
    fprintf(file, "File created successfully.\n");

    fclose(file);

    printf("File created: data/resource_log.txt\n");
}


void file_read_write_demo()
{
    printf("\n====================================\n");
    printf("          FILE READ / WRITE\n");
    printf("====================================\n");

    int fd = open("data/resource_state.txt",
                  O_CREAT | O_WRONLY | O_TRUNC,
                  0644);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    const char *message =
        "DeadlockDoctor Resource State\n"
        "R1 = Available\n"
        "R2 = Allocated\n";

    ssize_t written = write(fd, message, strlen(message));

    if (written == -1)
    {
        perror("write");
        close(fd);
        return;
    }

    printf("Data written successfully.\n");

    close(fd);

    fd = open("data/resource_state.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    char buffer[256];

    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes_read == -1)
    {
        perror("read");
        close(fd);
        return;
    }

    buffer[bytes_read] = '\0';

    printf("\nFile contents:\n");
    printf("%s", buffer);

    close(fd);

    printf("\nFile closed successfully.\n");
}


void file_descriptor_demo()
{
    printf("\n====================================\n");
    printf("          FILE DESCRIPTOR\n");
    printf("====================================\n");

    int fd = open("data/fd_test.txt",
                  O_CREAT | O_WRONLY | O_TRUNC,
                  0644);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    printf("File descriptor returned by open(): %d\n", fd);

    const char *message =
        "File descriptor represents an open file.\n";

    write(fd, message, strlen(message));

    printf("Data written using file descriptor.\n");

    close(fd);

    printf("File descriptor closed.\n");
}


void buffered_io_demo()
{
    printf("\n====================================\n");
    printf("          BUFFERED I/O\n");
    printf("====================================\n");

    FILE *file = fopen("data/buffered.txt", "w");

    if (file == NULL)
    {
        perror("fopen");
        return;
    }

    fprintf(file, "This data uses buffered I/O.\n");
    fprintf(file, "The C standard library manages the buffer.\n");

    fclose(file);

    printf("Buffered I/O completed using fopen() and fprintf().\n");
}


void unbuffered_io_demo()
{
    printf("\n====================================\n");
    printf("          UNBUFFERED I/O\n");
    printf("====================================\n");

    int fd = open("data/unbuffered.txt",
                  O_CREAT | O_WRONLY | O_TRUNC,
                  0644);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    const char *message =
        "This data uses unbuffered system-call I/O.\n";

    write(fd, message, strlen(message));

    close(fd);

    printf("Unbuffered I/O completed using write().\n");
}


void mmap_file_demo()
{
    printf("\n====================================\n");
    printf("       MEMORY-MAPPED FILE I/O\n");
    printf("====================================\n");

    const char *filename = "data/mmap_demo.txt";

    int fd = open(filename,
                  O_CREAT | O_RDWR | O_TRUNC,
                  0644);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    const char *message =
        "DeadlockDoctor memory mapped file demonstration.\n";

    size_t size = strlen(message);

    if (ftruncate(fd, size) == -1)
    {
        perror("ftruncate");
        close(fd);
        return;
    }

    char *mapped = mmap(NULL,
                        size,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED,
                        fd,
                        0);

    if (mapped == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return;
    }

    memcpy(mapped, message, size);

    msync(mapped, size, MS_SYNC);

    printf("File mapped into process memory.\n");
    printf("Mapped contents:\n");
    printf("%.*s", (int)size, mapped);

    munmap(mapped, size);

    close(fd);

    printf("Memory mapping released.\n");
}


void directory_demo()
{
    printf("\n====================================\n");
    printf("          DIRECTORY DEMO\n");
    printf("====================================\n");

    DIR *directory = opendir("data");

    if (directory == NULL)
    {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    printf("Files in data directory:\n");

    while ((entry = readdir(directory)) != NULL)
    {
        printf("%s\n", entry->d_name);
    }

    closedir(directory);
}


void filesystem_debug_demo()
{
    printf("\n====================================\n");
    printf("       FILE SYSTEM INFORMATION\n");
    printf("====================================\n");

    printf("\nUseful Linux commands:\n");

    printf("1. ls -li data/\n");
    printf("2. stat data/resource_state.txt\n");
    printf("3. df -T .\n");
    printf("4. df -Th .\n");

    printf("\nThese commands show:\n");
    printf("- Inode numbers\n");
    printf("- File metadata\n");
    printf("- File system type\n");
    printf("- Disk usage\n");
}
