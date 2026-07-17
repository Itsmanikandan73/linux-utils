#include <stdio.h>      // For standard I/O (Printf, fprintf)
#include <dirent.h>     // Crucial library for directory manipulation(DIR, opendir, readdir, closedir)
#include <errno.h>      // For extracting system error codes via 'errno'
#include <string.h>     // For strerror() to turn error codes into readable text

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr,"my_ls: cannot open '%s': %s\n", path, strerror(errno));
        return;
    }
    struct dirent *entry;

    while((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }
        printf("%s ", entry->d_name);
    }
    printf("\n");

    closedir(dir);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        list_directory(".");
    }
    else {
        for (int i = 1; i < argc; i++) {
            if (argc > 2) {
                printf("%s:\n", argv[i]);
            }
            list_directory(argv[i]);
            if (i < argc - 1) {
                printf("\n");
            }
        }
    }

    return 0;
}