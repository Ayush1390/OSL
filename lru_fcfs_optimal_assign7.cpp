#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <climits> 

using namespace std;

void displayFrames(const vector<int>& frames) {
    for (int page : frames)
        cout << page << " ";
    cout << "\n";
}

void fcfs(vector<int> pages, int capacity) {
    queue<int> q;
    unordered_set<int> inMemory;
    int pageFaults = 0;
    cout << "\nFCFS Page Replacement:\n";
    for (int page : pages) {
        if (inMemory.find(page) == inMemory.end()) {
            if (q.size() == capacity) {
                int removed = q.front();
                q.pop();
                inMemory.erase(removed);
            }
            q.push(page);
            inMemory.insert(page);
            pageFaults++;
        }
        cout << "Page " << page << " -> ";
        displayFrames(vector<int>(q.front(), q.back()));
    }
    cout << "Total Page Faults (FCFS): " << pageFaults << endl;
}

void lru(vector<int> pages, int capacity) {
    vector<int> frames;
    unordered_map<int, int> recent;
    int pageFaults = 0;
    cout << "\nLRU Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        auto it = find(frames.begin(), frames.end(), page);
        if (it == frames.end()) {
            if (frames.size() < capacity) {
                frames.push_back(page);
            } else {
                int lruIndex = 0, minTime = INT_MAX;
                for (int j = 0; j < frames.size(); j++) {
                    if (recent[frames[j]] < minTime) {
                        minTime = recent[frames[j]];
                        lruIndex = j;
                    }
                }
                frames[lruIndex] = page;
            }
            pageFaults++;
        }
        recent[page] = i;
        cout << "Page " << page << " -> ";
        displayFrames(frames);
    }
    cout << "Total Page Faults (LRU): " << pageFaults << endl;
}

void optimal(vector<int> pages, int capacity) {
    vector<int> frames;
    int pageFaults = 0;
    cout << "\nOptimal Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        auto it = find(frames.begin(), frames.end(), page);
        if (it == frames.end()) {
            if (frames.size() < capacity) {
                frames.push_back(page);
            } else {
                int replaceIndex = -1, farthest = i + 1;
                for (int j = 0; j < frames.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++) {
                        if (pages[k] == frames[j]) break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        replaceIndex = j;
                    }
                    if (k == pages.size()) {
                        replaceIndex = j;
                        break;
                    }
                }
                if (replaceIndex == -1) replaceIndex = 0;
                frames[replaceIndex] = page;
            }
            pageFaults++;
        }
        cout << "Page " << page << " -> ";
        displayFrames(frames);
    }
    cout << "Total Page Faults (Optimal): " << pageFaults << endl;
}

int main() {
    int n, capacity;
    vector<int> pages;
    cout << "Enter number of pages: ";
    cin >> n;
    pages.resize(n);
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }
    cout << "Enter number of frames: ";
    cin >> capacity;
    fcfs(pages, capacity);
    lru(pages, capacity);
    optimal(pages, capacity);

    return 0;
}
