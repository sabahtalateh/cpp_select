#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>

void read_and_report(int fd) {
    char buf[100];

    printf("FD [%d] is ready to read\n", fd);
    int bytes = read(fd, buf, 100);

    buf[bytes] = 0;

    printf("Get [%d bytes] from [%d] : %s\n", bytes, fd, buf);
}

int main() {
    int f1 = open("./f1.fifo", O_RDWR);
    int f2 = open("./f2.fifo", O_RDWR);

    if ((f1 == -1 || f2 == -1)) {
        printf("Error opening pipes\n");
        return 0;
    }

    printf("Descriptors [%d, %d]\n", f1, f2);

    fd_set read_set;

    while (true) {
        // Reset watch list
        FD_ZERO(&read_set);
        // Add file descriptors to watch-list
        FD_SET(f1, &read_set);
        FD_SET(f2, &read_set);

        // Block on watch-list instead of concrete descriptor
        int result = select(f2 + 1, &read_set, NULL, NULL, NULL);

        printf("RESULT IS %d\n", result);

        if (result) {
            if (FD_ISSET(f1, &read_set)) {
                read_and_report(f1);
            }
            if (FD_ISSET(f2, &read_set)) {
                read_and_report(f2);
            }
        }
    }

    return 0;
}