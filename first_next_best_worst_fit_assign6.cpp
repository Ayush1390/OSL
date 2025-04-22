#include <iostream>
#include <vector>
#include <limits>
using namespace std;

void firstFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1);

    for (int i = 0; i < processes.size(); i++) {
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;
                blocks[j] -= processes[i];
                break;
            }
        }
    }

    cout << "\nFirst Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "Process " << i + 1 << " of size " << processes[i]
             << " -> Block " << (allocation[i] != -1 ? to_string(allocation[i] + 1) : "Not Allocated") << endl;
    }
}

void bestFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1);

    for (int i = 0; i < processes.size(); i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                if (bestIdx == -1 || blocks[j] < blocks[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blocks[bestIdx] -= processes[i];
        }
    }

    cout << "\nBest Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "Process " << i + 1 << " of size " << processes[i]
             << " -> Block " << (allocation[i] != -1 ? to_string(allocation[i] + 1) : "Not Allocated") << endl;
    }
}

void worstFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1);

    for (int i = 0; i < processes.size(); i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blocks[worstIdx] -= processes[i];
        }
    }

    cout << "\nWorst Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "Process " << i + 1 << " of size " << processes[i]
             << " -> Block " << (allocation[i] != -1 ? to_string(allocation[i] + 1) : "Not Allocated") << endl;
    }
}

void nextFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1);
    int lastIndex = 0;
    int n = blocks.size();

    for (int i = 0; i < processes.size(); i++) {
        int count = 0;
        bool allocated = false;
        while (count < n) {
            int j = (lastIndex + count) % n;
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;
                blocks[j] -= processes[i];
                lastIndex = j;
                allocated = true;
                break;
            }
            count++;
        }
    }

    cout << "\nNext Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "Process " << i + 1 << " of size " << processes[i]
             << " -> Block " << (allocation[i] != -1 ? to_string(allocation[i] + 1) : "Not Allocated") << endl;
    }
}

int main() {
    int numBlocks, numProcesses;
    cout << "Enter number of memory blocks: ";
    cin >> numBlocks;

    vector<int> blocks(numBlocks);
    cout << "Enter sizes of memory blocks:\n";
    for (int i = 0; i < numBlocks; i++) cin >> blocks[i];

    cout << "Enter number of processes: ";
    cin >> numProcesses;

    vector<int> processes(numProcesses);
    cout << "Enter sizes of processes:\n";
    for (int i = 0; i < numProcesses; i++) cin >> processes[i];

    firstFit(blocks, processes);
    bestFit(blocks, processes);
    worstFit(blocks, processes);
    nextFit(blocks, processes);

    return 0;
}
