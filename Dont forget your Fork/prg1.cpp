/*
Parent and Child Process Identification

This simple program differentiates between the parent and the child using fork() and shows their respective Process IDs (PIDs).
*/

/*
#include <bits/stdc++.h>
using namespace std;

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
    }
    else if (pid == 0)
    {
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else
    {
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
    }

    return 0;
}
*/