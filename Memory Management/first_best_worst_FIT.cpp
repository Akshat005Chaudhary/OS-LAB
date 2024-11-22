#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
using namespace std;

// First Fit
void firstFit(vector<int> memoryBlocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1); // Initialize allocation to -1

    for (int i = 0; i < processes.size(); i++) {
        for (int j = 0; j < memoryBlocks.size(); j++) {
            if (memoryBlocks[j] >= processes[i]) {
                allocation[i] = j;
                memoryBlocks[j] -= processes[i];
                break;
            }
        }
    }

    cout << "First Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " not allocated\n";
    }
}

// Best Fit
void bestFit(vector<int> memoryBlocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1); // Initialize allocation to -1

    for (int i = 0; i < processes.size(); i++) {
        int bestIdx = -1;
        for (int j = 0; j < memoryBlocks.size(); j++) {
            if (memoryBlocks[j] >= processes[i]) {
                if (bestIdx == -1 || memoryBlocks[j] < memoryBlocks[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            memoryBlocks[bestIdx] -= processes[i];
        }
    }

    cout << "Best Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " not allocated\n";
    }
}

// Worst Fit
void worstFit(vector<int> memoryBlocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1); // Initialize allocation to -1

    for (int i = 0; i < processes.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < memoryBlocks.size(); j++) {
            if (memoryBlocks[j] >= processes[i]) {
                if (worstIdx == -1 || memoryBlocks[j] > memoryBlocks[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            memoryBlocks[worstIdx] -= processes[i];
        }
    }

    cout << "Worst Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        if (allocation[i] != -1)
            cout << "Process " << i + 1 << " allocated to Block " << allocation[i] + 1 << endl;
        else
            cout << "Process " << i + 1 << " not allocated\n";
    }
}

int main() {

    // memory_blocks: List of available memory block sizes.
    // processes: List of process sizes.

    vector<int> memoryBlocks = {100, 500, 200, 300, 600};
    vector<int> processes = {212, 417, 112, 426};

    cout << "Memory Blocks: ";
    for (int block : memoryBlocks) cout << block << " ";
    cout << "\nProcesses: ";
    for (int process : processes) cout << process << " ";
    cout << "\n\n";

    firstFit(memoryBlocks, processes);
    cout << "\n";
    bestFit(memoryBlocks, processes);
    cout << "\n";
    worstFit(memoryBlocks, processes);

    return 0;
}
