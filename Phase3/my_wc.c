#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>      // Crucial: Provides isspace() to check for tabs, spaces and newline
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 4096 // 4kb

void count_stream(int fd, const char *name) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    long long lines = 0;
    long long words = 0;
    long long bytes = 0;
    int in_word = 0;    // State flag: 0 means we are in whitespace, 1 means we are inside a word

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            char c = buffer[i];
            bytes++;

            if (c == '\n') {
                lines++;
            }
            // Mini state machine
            if (isspace((unsigned char)c)) {
                in_word = 0;    
            }
            else if (in_word == 0) {
                in_word = 1;
                words++;
            }
        }
    }
    if (bytes_read < 0) {
        fprintf(stderr,"My_wc: error reading %s: %s\n", name, strerror(errno));
    return;
    }

    if (name != NULL) {
        printf("%7lld %7lld %7lld %s\n", lines, words, bytes, name);
    }
    else {
        printf("%7lld %7lld %7lld %s\n", lines, words, bytes);
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        count_stream(STDIN_FILENO, NULL);
        return 0;
    }

    for (int i = 0; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        
        if (fd < 0) {
            fprintf(stderr, "My_wc: %s: %s\n", argv[i], strerror(errno));
            continue;
        }
        count_stream(fd, argv[i]);
        close(fd);
    }

    return 0;
}
