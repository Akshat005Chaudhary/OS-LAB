/*

Creating Multiple Child Processes

You can use fork() multiple times to create more than one child process.
This program demonstrates how to create two child processes.

*/

/*

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 < 0) {
        printf("Fork failed!\n");
    } else if (pid1 == 0) {
        printf("First child: PID = %d\n", getpid());
    } else {
        pid_t pid2 = fork();
        if (pid2 < 0) {
            printf("Fork failed!\n");
        } else if (pid2 == 0) {
            printf("Second child: PID = %d\n", getpid());
        } else {
            // Parent waits for both children
            wait(NULL);
            wait(NULL);
            printf("Both children completed, Parent resuming\n");
        }
    }

    return 0;
}

*/