#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    int res;
    res = open("fifo", O_WRONLY);
    if (res == -1) {
        perror("Opening FIFO failed");
        return 1;
    }
    char msg[100];
    printf("Enter a message to send: ");
    fgets(msg, sizeof(msg), stdin);

    write(res, msg, sizeof(msg)); 
    printf("Writer process %d sent the data\n", getpid());

    close(res); 
    return 0;
}