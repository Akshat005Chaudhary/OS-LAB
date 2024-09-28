/*

Using fork() with wait()

The wait() system call allows the parent process to wait until the child process finishes execution. This is often used for synchronization between processes.

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
        sleep(2); // Simulating some work in the child process
        printf("Child process completed\n");
    } else {
        printf("Parent process: Waiting for the child to complete\n");
        wait(NULL); // Parent waits for child to finish
        printf("Child completed, Parent resuming\n");
    }

    return 0;
}


*/
