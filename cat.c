#include <stdio.h>      // For standard I/O (like fprintf and perror)
#include <fcntl.h>      // For open() and the O_RDONLY flag
#include <unistd.h>     // For low-level system calls: read(), write(), close()
#include <string.h>     // For strerror() to translate error codes to English
#include <errno.h>      // For the global 'errno' variable to catch system errors

#define BUFFER_SIZE 4096;

void cat_stream(int fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read == read(fd, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_read);

        if (bytes_written < 0) {
            perror("Error writing to stdout")
            return;
        }
    }
    if (bytes_read < 0) {
        perror("Error reading file");
    }
}

int main(int argc, char *argv){


    return 0;
}