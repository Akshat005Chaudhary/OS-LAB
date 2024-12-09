// MESSAGE QUEUE (READER PROCESS)
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
    int msgid;

    // Generate unique key
    key = ftok("progfile", 'A');

    // Access the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Receive message from the queue
    if (msgrcv(msgid, &svarname, sizeof(svarname.mtext), 1, 0) == -1) {
        perror("msgrcv failed");
        return 1;
    }

    // Print received message
    printf("Data Received is: %s\n", svarname.mtext);

    // Remove message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        return 1;
    }

    return 0;
}
