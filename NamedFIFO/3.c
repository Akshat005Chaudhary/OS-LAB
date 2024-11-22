#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    int res, n;
    char buffer[100];
    res = open("fifo", O_RDONLY);
    if (res == -1) {
        perror("Opening FIFO failed");
        return 1;
    }

    n = read(res, buffer, sizeof(buffer));
    if (n >= 0) {
        buffer[n] = '\0'; 
        printf("Reader process %d received: %s\n", getpid(), buffer);
    } else {
        printf("No data read by reader %d\n", getpid());
    }

    close(res);
    return 0;
}