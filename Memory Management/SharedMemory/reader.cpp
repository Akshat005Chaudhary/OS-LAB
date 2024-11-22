#include <iostream>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
using namespace std;

int main()
{
    // ftok to generate unique key
    // Unique key based on file shmfile and identifier 65
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    // Creates a memory segment of size 1024 bytes
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    // shmat attaches the shared memory segment to the process's address space, returning a pointer to it.
    char* str = (char*)shmat(shmid, (void*)0, 0);

    cout << "Data read from memory:" << str;

    // detach from shared memory
    shmdt(str);

    // destroy the shared memory
    // Must be done in the reader process to cleanup
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
