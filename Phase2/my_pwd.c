#include <stdio.h>      // For input/output functions like printf and fprintf
#include <unistd.h>     // For getcwd(), the POSIX system call to get the current directory
#include <limits.h>     // For PATH_MAX, a system-defined constant for  maximum path length
#include <errno.h>      // For errno, a global variable that holds system error codes
#include <string.h>     // For strerror(), which turns, error codes into readable text

int main(void) {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    }
    else {
        fprintf(stderr, "My_pwd error: %s\n", strerror(errno));
        return 1;
    }
    
    return 0;
}