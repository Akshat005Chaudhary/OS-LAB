/*

exec() with fork()

fork() creates a new process, but you can use exec() to run a new program within the child process.
This is useful for creating a new process that executes a different program.

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
        // Child process: replacing itself with the `ls` command

        // Format of execl:
        // 1st arg = path to directory to access executable from
        // 2nd arg = name of the executable
        // 3rd arg = other arguments that need be passed to the executable
        // NULL = indicates the end of arguments

        execl("/bin/ls", "ls", "-l", NULL);
        printf("This won't print if execl() is successful\n");
    } else {
        // Parent process waits for the child to finish
        wait(NULL);
        printf("Parent process: Child has completed execution\n");
    }

    return 0;
}

*/