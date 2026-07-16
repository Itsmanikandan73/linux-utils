#include <stdio.h>      // Provides printf for outputting text to the screen
#include <string.h>     // Provides strcmp for comparing text strings
#include <stdbool.h>    // Provides the 'bool' type (true/false values)

int main(int argc, char *argv[]) {

    int start_index = 1;
    bool omit_newline = false;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        omit_newline = true;
        start_index = 2;    
    }

    for (int i = start_index; i < argc; i++) {
        printf("%s", argv[i]);

        if (i < argc - 1) {
            printf(" ");
        }
    }

    if (!omit_newline) {
        printf("\n");
    }

    return 0;
}