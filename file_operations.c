#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
    int fd;                  // File descriptor
    ssize_t bytes_written;   // Number of bytes written

    printf("Creating file: %s\n", filename);
    printf("Content to write: %s\n", content);

    // Open or create file with flags and permissions
    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    printf("File descriptor: %d\n", fd);

    // Write content into the file
    bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return -1;
    }

    printf("Successfully wrote %zd bytes to '%s'\n", bytes_written, filename);

    // Close file
    if (close(fd) == -1) {
        perror("close");
        return -1;
    }

    printf("File closed successfully\n");
    return 0;
}

int read_file_contents(const char *filename) {
    int fd;                  // File descriptor
    char buffer[1024];       // Buffer to hold file data
    ssize_t bytes_read;      // Number of bytes read

    printf("Reading file: %s\n", filename);

    // Open file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    printf("File descriptor: %d\n", fd);
    printf("\n--- Contents of '%s' ---\n", filename);

    // Read file in chunks
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0'; // Null terminate
        printf("%s", buffer);
    }

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return -1;
    }

    printf("\n--- End of file ---\n");

    // Close file
    if (close(fd) == -1) {
        perror("close");
        return -1;
    }

    printf("File closed successfully\n");
    return 0;
}
