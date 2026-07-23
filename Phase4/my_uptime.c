#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void print_updtime(void) {
    int fd = open("/proc/uptime", O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "my_uptime: cantnot open /proc/uptime: %s\n", strerror(errno));
        return;
    }

    char buffer[128];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) -1);
    close(fd);

    if (bytes_read <= 0) {
        fprintf(stderr,"my_uptime: failded to read /proc/uptime\n");
        return;
    }

    buffer[bytes_read] = '\0';

    // Parse the total seconds powered on (first float in the file)
    double uptime_seconds = 0.0;
    if (sscanf(buffer, "%lf", &uptime_seconds) != 1) {
        fprintf(stderr,"my_uptime: failed to parse uptime data\n");
        return;
    }

    long total_sec = (long)uptime_seconds;
    int days = total_sec / 86400;
    int hours = (total_sec % 86400) / 3600;
    int mins = (total_sec % 3600) / 60;
    int secs = total_sec % 60;

    printf("System Uptime: ");
    if (days > 0) {
        printf("%d days, ",days);
    }
    printf("%02d hours, %02d minutes, %02d seconds\n", hours, mins, secs);
}

int main(void) {
    print_updtime();
    return 0;
}