// Week 1: Demonstration of fork() system call

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