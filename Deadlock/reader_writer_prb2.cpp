/* 
Pseudo Code:

Writer:
wait(mutex)
write()
signal(mutex)

Reader:
reader_cnt++
if(reader_cnt==1) wait(mutex);
read()
read_cnt--;
if(read_cnt==0) signal(mutex)

*/


/*

CPP Implementation of Problem II:

the classic reader-writer problem with a flaw: after a writer finishes, the first reader is correctly 
blocked to maintain synchronization, but subsequent readers are allowed to proceed without proper 
synchronization, which can lead to inconsistent data access. This issue often arises when the 
reader_count is not managed correctly.

*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
using namespace std;

mutex rw_mutex;        
mutex reader_count_mutex;  
int shared_data = 0;
int reader_count = 0;

void reader(int id) {
    reader_count_mutex.lock();
    reader_count++;
    if (reader_count == 1) {
        rw_mutex.lock(); 
    }
    reader_count_mutex.unlock();

    cout << "Reader " << id << " is reading data: " << shared_data << endl;
    this_thread::sleep_for(chrono::milliseconds(1500)); 
    cout << "Reader " << id << " finished reading." << endl;

    reader_count_mutex.lock();
    reader_count--;
    if (reader_count == 0) {
        rw_mutex.unlock();
    }
    reader_count_mutex.unlock();
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
