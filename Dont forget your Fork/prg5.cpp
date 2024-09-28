/*

Orphan Process

An orphan process is a child process whose parent has terminated. In this example, the parent process finishes before the child, making the child an orphan.

*/

/*

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
    } else if (pid == 0) {
        sleep(5); // Child sleeps, waiting for parent to finish first
        printf("Orphaned child: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        printf("Parent process: Terminating before child\n");
        return 0; // Parent terminates
    }

    return 0;
}

*/