#include <stdio.h>      // For printing out text and error message (fprintf, stderr)
#include <sys/stat.h>   // Provides the actual mkdir() system function call
#include <sys/types.h>  // Defines data types used by system calls (like mode_t)
#include <errno.h>      // Gives access to 'errno' to catch low-level system errors
#include <string.h>     // Provides strerror() to turn error codes into english words

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr,"my_mkdir: missing operand\n");
        fprintf(stderr,"Usage: %s <directory_name>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char *dir_name = argv[i];

        if (mkdir(dir_name, 0777) != 0) {
            fprintf(stderr,"my_mkdir: cannot create directoyr '%s': %s\n",dir_name, strerror(errno));
            return 1;
        }
    }
    return 0;
}