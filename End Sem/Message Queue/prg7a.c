// MESSAGE QUEUE (WRITER PROCESS)
#include <stdio.h>                                        
  
  
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

// Structure for message queue
struct msgbuf {
    long mtype;
    char mtext[100];
} svarname;

int main() {
    key_t key;
    int msgid, c;

    // Generate unique key
    key = ftok("progfile", 'A');

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Set message type
    svarname.mtype = 1;

    // Take input from user
    printf("\nEnter a string: ");
    fgets(svarname.mtext, sizeof(svarname.mtext), stdin);

    // Remove trailing newline character if present
    size_t len = strlen(svarname.mtext);
    if (len > 0 && svarname.mtext[len - 1] == '\n') {
        svarname.mtext[len - 1] = '\0';
    }

    // Send message to the queue
    c = msgsnd(msgid, &svarname, sizeof(svarname.mtext), 0);

    if (c == -1) {
        perror("msgsnd failed");
        return 1;
    }

    // Print message sent
    printf("Sender wrote the text: %s\n", svarname.mtext);

    return 0;
}

