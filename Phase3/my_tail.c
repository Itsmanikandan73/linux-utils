#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_LINES 10

void tail_file(int fd, int target_lines) {
    char c;
    long long line_count = 0;

    off_t file_size = lseek(fd , 0, SEEK_END);
    if (file_size <= 0) return;

    off_t offset = file_size;

    while (offset > 0) {
        offset--;
        lseek(fd, offset, SEEK_SET);

        if (read(fd, &c, 1) <= 0) break;

        if (c == '\n' && offset != file_size - 1) {
            line_count++;
            if (line_count == target_lines) {
                offset++;
                break;
            }
        }
    }

    lseek(fd, offset, SEEK_SET);

    char buffer[4096];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
}

int main(int argc, char *argv[]) {

    int lines = DEFAULT_LINES;
    int file_index = 1;

    if (argc > 2 && strcmp(argv[1], "-n") == 0) {
        lines = atoi(argv[2]);
        file_index = 3;
    }

    if (file_index >= argc) {
        fprintf(stderr,"NOTE: This simple tail implementation requires a file argument to seek backwards.\n");
        return 1;
    }

    int fd = open(argv[file_index], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr,"my_tail: %s: %s\n", argv[file_index], strerror(errno));
        return 1;
    }

    tail_file(fd, lines);
    close(fd);
    return 0;
}