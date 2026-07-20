#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>

// Helper for case-insentive string search (-i flag)
void *strcasestr_custom(const char *haystack, const char *needle) {
    if (!*needle) return (char *)haystack;

    for (; *haystack; haystack++) {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)){
            const char *h = haystack + 1;
            const char *n = needle + 1;
            while (*h && &*n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
                h++;
                n++;
            }
            if (!*n) return (char *)haystack;
        }
    }
    return NULL;
}

void grep_strem(FILE *fp, const char *pattern, const char *filename, bool ignore_case, bool line_numbers, bool show_file) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    long line_num = 0;

    // Read the file line-by-line using POSIX getline()
    while ((read = getline(&line, &len, fp)) != -1) {
        line_num++;

        // search for pattern match based on case sensitivity flag
        char *match = ignore_case ? strcasestr_custom(line, pattern): strstr(line, pattern);

        if (match != NULL) {
            // Print prefix info (filename and/or line number) if needed
            if (show_file && filename != NULL) {
                printf("%s:", filename);
            }
            if (line_numbers) {
                printf("%ld:", line_num);
            }
            printf("%s", line);
        }

    }
    free(line); // free the dynamic memory buffer allocated by getline
    
}

int main(int argc, char *argv[]) {
    bool ignore_case = false;
    bool line_numbers = false;
    int arg_idx = 1;

    // Parse command line flags (-i, -n)
    while (arg_idx < argc && argv[arg_idx][0] == '-' && argv[arg_idx][1] !='\0') {
        char *flag = argv[arg_idx] + 1;
        while (*flag) {
            if (*flag == 'i') ignore_case = true;
            else if (*flag == 'n') line_numbers = true;
            else {
                fprintf(stderr, "my_grep: unknown option -- %c\n", *flag);
                return 1;
            }
            flag++;
        }
        arg_idx++;
    }

    if (arg_idx >= argc) {
        fprintf(stderr, "Usage: %s [-n] PATTERN [FILE....]\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[arg_idx++];
    int files_count = argc - arg_idx;

    // Fallback to standard input if no file paths were provided 
    if (files_count == 0) {
        grep_strem(stdin, pattern, NULL, ignore_case, line_numbers, false);
        return 0;
    }

    // Process all provided files 
    for (int i = arg_idx; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "my_grep: %s: %s\n", argv[i], strerror(errno));
            continue;
        }
        // Show filename prefix if searching across multiple files
        bool show_filename = (files_count > 1);
        grep_strem(fp, pattern, argv[i], ignore_case, line_numbers, show_filename);
        fclose(fp);
    }

    return 0;
}