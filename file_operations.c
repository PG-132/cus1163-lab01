#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
    int fd = 0;
    ssize_t bytes_written = 0;

    printf("Creating file: %s\n", filename);
    printf("Content to write: %s\n", content);

    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    printf("File descriptor: %d\n", fd);

    bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return -1;
    }
    printf("Wrote %d bytes to %s\n", bytes_written, filename);

    if (close(fd) == -1) {
        perror("close");
        return -1;
    }

    return 0;
}

int read_file_contents(const char *filename) {
    int fd = 0;
    char buffer[1024];
    ssize_t bytes_read;

    printf("Reading file: %s\n", filename);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    printf("File descriptor: %d\n, fd");
    printf("File Contents----\n");

    while((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return -1;
    }

    printf("\n END OF FILE");

    if (close(fd) == -1) {
        perror("close");
        return -1;
    }

    printf("File closed successfully\n");
    
    return 0;
}
