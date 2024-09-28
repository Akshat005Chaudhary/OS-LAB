/*

Piping Between Parent and Child Processes

This program demonstrates how two processes (parent and child) can communicate using pipes.

*/

/*

This program demonstrates interprocess communication (IPC) between a parent and a child process using a pipe. A pipe is a unidirectional communication channel that allows data to flow from one process to another, specifically from the child process to the parent in this example.


Step-by-Step Explanation

File Descriptors (fd[2]):
The array fd[2] holds two file descriptors:
fd[0]: The reading end of the pipe.
fd[1]: The writing end of the pipe.

Creating the Pipe:
pipe(fd) is called to create the pipe. After this call, fd[0] can be used to read data, and fd[1] can be used to write data.

Forking a Child Process:
fork() is used to create a child process. After this call:
The parent process gets the child's PID.
The child process gets a PID of 0.

Child Process:
The child process executes the code in the if (pid == 0) block.
Close the reading end: The child closes fd[0] because it will only write to the pipe and doesn’t need to read from it.
Writing to the pipe: The child writes the message "Hello from the child process!" to the pipe using the write(fd[1], ...) system call.
Close the writing end: After writing, the child closes fd[1] to signal that it's done writing.

Parent Process:
The parent process executes the else block.
Close the writing end: The parent closes fd[1] because it will only read from the pipe and doesn’t need to write.
Reading from the pipe: The parent reads data from the pipe using the read(fd[0], ...) system call and stores it in the buffer.
Print the message: The parent prints the message it received from the child: "Parent received: Hello from the child process!".
Close the reading end: After reading, the parent closes fd[0].


Execution Flow

Parent Process:
The parent process starts and creates the pipe.
It then forks the child process.

Child Process:
The child process writes a message to the pipe and terminates after closing its end of the pipe.

Parent Process:
The parent reads the message from the pipe after the child has written to it.
It then prints the message it received from the child.


Key Concepts
Pipe: A pipe is used to pass data between two processes. It provides a one-way communication channel.
File Descriptors: These are integers representing open files or communication channels. In this case, fd[0] is used for reading from the pipe and fd[1] is used for writing to it.
Fork: fork() creates a new process by duplicating the calling process. After fork(), there are two processes (parent and child), and they execute different parts of the code.
Closing unused ends: It’s important to close the unused end of the pipe in both the parent and child processes to prevent issues such as deadlocks or writing/reading errors.


Why Close Unused Ends of the Pipe?

Closing the unused end of the pipe is crucial because:
If the child process doesn’t close the reading end (fd[0]), the pipe will remain open on both ends, and write() may block waiting for the parent to read.
If the parent doesn’t close the writing end (fd[1]), read() in the parent might not return as it expects the writing end to be closed to signify the end of the data.

*/

/*

#include <stdio.h>
#include <unistd.h>

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

*/

/*

// CPP Code for Piping

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

int main() {
    int pipe_fd[2]; // Array to hold pipe file descriptors
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        std::cerr << "Pipe failed!" << std::endl;
        return 1;
    }

    // Fork a child process
    pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid > 0) {
        // Parent process
        close(pipe_fd[0]); // Close the read end of the pipe

        // Write message to the pipe
        write(pipe_fd[1], write_msg, strlen(write_msg) + 1);

        close(pipe_fd[1]); // Close the write end of the pipe

        // Wait for the child to finish
        wait(NULL);
    } else {
        // Child process
        close(pipe_fd[1]); // Close the write end of the pipe

        // Read message from the pipe
        read(pipe_fd[0], read_msg, sizeof(read_msg));

        std::cout << "Child received: " << read_msg << std::endl;

        close(pipe_fd[0]); // Close the read end of the pipe
    }

    return 0;
}


*/