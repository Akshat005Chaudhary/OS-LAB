/*

Zombie Process

A zombie process is a terminated child process that still has an entry in the process table.
This happens if the parent does not use wait() to clean up after the child process.

*/

/*

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
    } else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        return 0; // Child process terminates immediately
    } else {
        sleep(5); // Parent sleeps, allowing child to become a zombie
        printf("Parent process: Child is now a zombie\n");
        // Even though the child process has left
        // the parent process hasn't acknowledged its exit
        // therefore wait() is necessary
        wait(NULL); // Clean up the zombie process
        printf("Parent process: Zombie cleaned up\n");
    }

    return 0;
}

*/