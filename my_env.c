#include <stdio.h>

// Declare the external global environment array provided by the C runtime.
extern char **environ;

int main(int argc, char **argv) {
    // if someone passes arguments, notify them (a full 'env' can run commands)
    // but for our core utility, we focus on priting the environment.
    (void) argc;
    (void) argv;

    // Pointer to traverse the NULL - terminated array of strings.
    char **env = environ;

    if (env == NULL) {
        fprintf(stderr, "my_env: environment is empty or unavailable\n");
        return 1;
    }

    // Loop until we hit the NULL pointer at the end of the array
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;  // Move pointer to the next string address
    }
    return 0;
}