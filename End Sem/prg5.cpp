// Implementation of PIPE

#include <bits/stdc++.h>

int main() {
    int fd[2];  // File descriptors for the pipe
    pipe(fd);   // Create a pipe

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
    } else if (pid == 0) {
        // Child process: write to pipe
        close(fd[0]);  // Close reading end
        char message[] = "Hello from the child process!";
        write(fd[1], message, sizeof(message));
        close(fd[1]);
    } else {
        // Parent process: read from pipe
        close(fd[1]);  // Close writing end
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(fd[0]);
    }

    return 0;
}