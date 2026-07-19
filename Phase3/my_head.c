#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_LINES 10

void head_stream(int fd, int target_line) {
    char c;
    int lines_printed = 0;

    if (target_line <= 0) return;

    while (read(fd, &c, 1) > 0) {
        if (write(STDOUT_FILENO, &c, 1) < 0){
            perror("Error writing to stdout");
            return;
        }

        if (c == '\n'){
            lines_printed++;
            if (lines_printed >= target_line) {
                break;
            }
        }
    }
}

int main(int argc, char **argv) {

    int lines = DEFAULT_LINES;
    int file_index = 1;

    if (argc > 2 && strcmp(argv[1], "-n") == 0) {
        lines = atoi(argv[2]);
        file_index = 3;
    }

    if (file_index >= argc) {
        head_stream(STDIN_FILENO, lines);
        return 0;
    }
    
    int fd = open(argv[file_index], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "My_head: %s: %s\n", argv[file_index], strerror(errno));
        return 1;
    }

    head_stream(fd, lines);
    close(fd);
    return 0;
}