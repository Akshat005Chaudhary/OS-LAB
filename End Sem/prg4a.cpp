// Implementation of Orphan Process

#include <bits/stdc++.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
    } else if (pid == 0) {
        sleep(2); // Child sleeps, waiting for parent to finish first
        printf("Orphaned child: PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        printf("Parent process: Terminating before child\n");
        wait(NULL);
    }

    return 0;
}