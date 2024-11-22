/*
 We can combine the code for creating the FIFO, writing to it, 
 and reading from it into a single C file. 
 However, since the writer and reader need to run concurrently, 
 you’ll need to use forking to create separate processes within the same program.
*/



#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int res;
    pid_t pid;

    res = mkfifo("fifo", 0777);
    if (res == -1) {
        perror("FIFO creation failed");
        return 1;
    }
    printf("Named pipe created\n");

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        int res_read;
        char buffer[100];
        
        res_read = open("fifo", O_RDONLY);
        if (res_read == -1) {
            perror("Opening FIFO for reading failed");
            return 1;
        }
        
        int n = read(res_read, buffer, sizeof(buffer));
        if (n >= 0) {
            buffer[n] = '\0';
            printf("Reader process %d received: %s\n", getpid(), buffer);
        } else {
            printf("No data read by reader %d\n", getpid());
        }
        
        close(res_read);
    } else {
        int res_write;
        char msg[100];

        res_write = open("fifo", O_WRONLY);
        if (res_write == -1) {
            perror("Opening FIFO for writing failed");
            return 1;
        }

        printf("Enter a message to send: ");
        fgets(msg, sizeof(msg), stdin); 

        write(res_write, msg, strlen(msg));
        printf("Writer process %d sent the data: %s", getpid(), msg);

        close(res_write);

        wait(NULL);
    }

    return 0;
}
