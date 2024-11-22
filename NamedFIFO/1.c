#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int res;
    res = mkfifo("fifo", 0777);
    if (res == -1) {
        perror("FIFO creation failed");
        return 1;
    }
    printf("Named pipe created\n");
    return 0;
}