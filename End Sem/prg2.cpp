// Parent process computes the sum of even and child process computes the sum of odd numbers using fork()

#include <bits/stdc++.h>
// #include <unistd.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter the range (1 to n): ";
    cin >> n;

    pid_t pid = fork();

    if (pid < 0)
    {
        cerr << "Fork failed!" << endl;
        return 1;
    }
    else if (pid == 0) // Child process
    {
        int odd_sum = 0;
        for (int i = 1; i <= n; i++)
        {
            if (i % 2 != 0)
            {
                odd_sum += i;
            }
        }
        printf("Child process: Sum of odd numbers = %d\n", odd_sum);
    }
    else // Parent process
    {
        int even_sum = 0;
        for (int i = 1; i <= n; i++)
        {
            if (i % 2 == 0)
            {
                even_sum += i;
            }
        }
        printf("Parent process: Sum of even numbers = %d\n", even_sum);
    }

    return 0;
}
