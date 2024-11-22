/*

The Dining Philosophers Problem is a classic concurrency and synchronization problem in computer science that illustrates potential deadlock, starvation, and mutual exclusion issues. The problem involves five philosophers sitting around a circular table, each of whom alternates between thinking and eating. Between each philosopher is a single fork, which the philosophers need to eat.

Here’s the setup:

Five Philosophers: Each philosopher sits at the table with a fork placed between them.
Thinking and Eating: Philosophers alternate between thinking and eating.
Forks: To eat, each philosopher needs two forks: the one to their left and the one to their right.
Constraints: Philosophers can only eat when they have access to both adjacent forks. They cannot share or pass forks while eating.

Problem Outline
Resource Contention: Philosophers must compete for the limited forks, making this a problem of resource allocation.
Deadlock: If each philosopher picks up the fork on their right and waits indefinitely for the fork on their left, a deadlock occurs (no philosopher can eat because each is holding one fork).
Starvation: A philosopher could starve if they never get access to both forks due to others constantly using them.

Solution:
Philosophers are assigned an order in which they pick up forks.
For instance, odd-numbered philosophers pick up the left fork first, and even-numbered ones pick up the right fork first.
This reduces deadlock because at least one philosopher will always get both forks, allowing the cycle to break.

Cons of this solution:
Even though this solution resolves deadlock, we have poor resource management as just because 2 forks are occupied
the philosopher not adjacent to eating philosopher will also not be able to use the avaliable fork
Also ideally, multiple philosophers should be able to eat at the same time if resources are available. However, in this approach, the "hold-and-wait" behavior limits this parallelism, as philosophers may hold forks unnecessarily.

*/


// CPP Implementation:

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

const int NUM_PHILOSOPHERS = 5;
std::vector<std::mutex> forks(NUM_PHILOSOPHERS);  // One fork between each philosopher

void philosopher(int id) {
    int leftFork = id;                   // Left fork is the philosopher's own fork
    int rightFork = (id + 1) % NUM_PHILOSOPHERS;  // Right fork is the next one in the circle

    while (true) {
        // Thinking
        std::cout << "Philosopher " << id << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simulate thinking

        // Pick up forks (locking in order to avoid deadlock)
        if (id % 2 == 0) {  // Even philosopher picks up the left fork first
            forks[leftFork].lock();
            forks[rightFork].lock();
        } else {  // Odd philosopher picks up the right fork first
            forks[rightFork].lock();
            forks[leftFork].lock();
        }

        // Eating
        std::cout << "Philosopher " << id << " is eating.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simulate eating

        // Put down forks
        forks[leftFork].unlock();
        forks[rightFork].unlock();
    }
}

int main() {
    // Initialize and start philosopher threads
    std::vector<std::thread> philosophers;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.push_back(std::thread(philosopher, i));
    }

    // Join philosopher threads (they will run indefinitely in this simulation)
    for (auto& phil : philosophers) {
        phil.join();
    }

    return 0;
}



/*


Here's a C++ implementation of the Dining Philosophers Problem using mutexes to handle the synchronization of forks:

cpp
Copy code
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

const int NUM_PHILOSOPHERS = 5;
std::vector<std::mutex> forks(NUM_PHILOSOPHERS);  // One fork between each philosopher

void philosopher(int id) {
    int leftFork = id;                   // Left fork is the philosopher's own fork
    int rightFork = (id + 1) % NUM_PHILOSOPHERS;  // Right fork is the next one in the circle

    while (true) {
        // Thinking
        std::cout << "Philosopher " << id << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simulate thinking

        // Pick up forks (locking in order to avoid deadlock)
        if (id % 2 == 0) {  // Even philosopher picks up the left fork first
            forks[leftFork].lock();
            forks[rightFork].lock();
        } else {  // Odd philosopher picks up the right fork first
            forks[rightFork].lock();
            forks[leftFork].lock();
        }

        // Eating
        std::cout << "Philosopher " << id << " is eating.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Simulate eating

        // Put down forks
        forks[leftFork].unlock();
        forks[rightFork].unlock();
    }
}

int main() {
    // Initialize and start philosopher threads
    std::vector<std::thread> philosophers;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers.push_back(std::thread(philosopher, i));
    }

    // Join philosopher threads (they will run indefinitely in this simulation)
    for (auto& phil : philosophers) {
        phil.join();
    }

    return 0;
}
Explanation:

Mutex Array (Forks): We create a std::vector of std::mutex objects, where each mutex represents a fork.

Threaded Philosophers: Each philosopher is represented by a thread that alternates between thinking and eating.

Deadlock Avoidance:
To prevent deadlock, each philosopher follows an alternating locking order:
Even philosophers pick up the left fork first.
Odd philosophers pick up the right fork first.

Execution:
Philosophers think (simulate with sleep), pick up forks (lock the mutexes), eat (simulate with sleep), and then put down forks (unlock the mutexes).

This approach prevents deadlock by ensuring that not all philosophers attempt to acquire the same two forks simultaneously.

*/