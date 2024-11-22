// Here we are demonstrating the case where we suffer from reader writer problem.
// Solution to the problem is not part of operating system but of DBMS where we make
// use of lock to prevent it.


/*

What is Reader-Writer Problem?
In an ideal system the allowed scenarios for multi-threading/processing:
R-R -> Allowed
W-R, R-W, W-W -> Not Allowed

Now two problems might arises from this, if the exemplary cases are not followed as they are:
1) Multiple readers might have to wait even if the precursor thread was for reading, this happens when 
R-R is not followed
2) Race condition might if W-R / R-W / W-W is not followed, where the final data is not what it should be
after the transactions

*/

/*
Pseudo Code:

Writer:
wait(mutex)
write()
signal(mutex)

Reader:
wait(mutex)
read()
signal(mutex)

*/


/*

CPP Implementation of problem I:

Here we will take diff-diff scenarios:
W-W, W-R, R-W will be blocked as the should to prevent Reader-Writer Problem
But, R-R which ideally should'nt be blocked will be nevertheless.
This will make multiple readers to wait unnecessarily demonstrating Reader-Writer Problem 
and also proving that the proposed solution is incorrect 

*/


#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
using namespace std;

mutex rw_mutex;
int shared_data = 0;

void reader(int id) {
    cout << "Reader " << id << " is waiting to read." << endl;
    rw_mutex.lock();
    cout << "Reader " << id << " is reading data: " << shared_data << endl;
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Reader " << id << " finished reading." << endl;
    rw_mutex.unlock();
}

void writer(int id) {
    cout << "Writer " << id << " is waiting to write." << endl;
    rw_mutex.lock();
    shared_data++;
    cout << "Writer " << id << " is writing data: " << shared_data << endl;
    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << "Writer " << id << " finished writing." << endl;
    rw_mutex.unlock();
}

int main() {
    vector<thread> readers;
    vector<thread> writers;

    //  One can change this order to explore of the R-R / W-R / R-W / W-W scenarios 

    writers.push_back(thread(writer, 1));
    this_thread::sleep_for(chrono::milliseconds(100));

    readers.push_back(thread(reader, 1));
    readers.push_back(thread(reader, 2)); 
    readers.push_back(thread(reader, 3));

    writers.push_back(thread(writer, 2));

    for (auto& th : readers) th.join();
    for (auto& th : writers) th.join();

    return 0;
}
