#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h> 
#include <errno.h>

void print_usage(const char *program_name) {
    fprintf(stderr, "Usage: %s [-SIGNAL] PID...\n", program_name);
    fprintf(stderr, "Example: %s -9 1234\n", program_name);
    fprintf(stderr, "Example: %s 1234\n", program_name);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    int signal_num = SIGTERM; //Default signal is 15 (SIGTERM)
    int pid_start_index = 1;

    // Check if the first argument specifies a signal (eg. -1 or 15)
    if (argv[1][0] == '-') {
        // Convert string after '-' to an integer
        signal_num = atoi(&argv[1][1]);
        
        if (signal_num <= 0) {
            fprintf(stderr, "my_kill: invalid signal specification '%s'\n", argv[1]);
            return 1;
        }

        pid_start_index = 2;    // PIDs begin at index 2
    }

    if (pid_start_index >= argc) {
        fprintf(stderr,"my_kill: missing PID oprand\n");
        print_usage(argv[0]);
        return 1;
    }

    // Iterate through all provided PIDs and deliver the signal
    for (int i = pid_start_index; i < argc; i++) {
        pid_t pid = (pid_t) atoi(argv[i]);

        if (pid <= 0) {
            fprintf(stderr, "my_kill: invalid PID '%s'\n", argv[i]);
            continue;
        }

        // The kill() system call 
        if (kill(pid, signal_num) != 0) {
            fprintf(stderr, "my_kill: sending signal %d to PID %d failed: %s\n", signal_num, pid, strerror(errno));
        } 
        else {
            printf("Successfully sent signal %d to process %d\n", signal_num, pid);
        }
    }
}