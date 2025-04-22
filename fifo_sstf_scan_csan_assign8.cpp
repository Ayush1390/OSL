#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits> 

using namespace std;

void fifo(const vector<int>& requests, int head) {
    int seek_time = 0;
    int current = head;
    cout << "\nFIFO Order: ";
    for (int req : requests) {
        cout << req << " ";
        seek_time += abs(current - req);
        current = req;
    }
    cout << "\nTotal Seek Time (FIFO): " << seek_time << endl;
}

void sstf(vector<int> requests, int head) {
    int seek_time = 0;
    int current = head;
    vector<bool> visited(requests.size(), false);
    cout << "\nSSTF Order: ";

    for (int i = 0; i < requests.size(); ++i) {
        int min_dist = INT_MAX;
        int index = -1;
        for (int j = 0; j < requests.size(); ++j) {
            if (!visited[j] && abs(current - requests[j]) < min_dist) {
                min_dist = abs(current - requests[j]);
                index = j;
            }
        }
        visited[index] = true;
        seek_time += min_dist;
        current = requests[index];
        cout << current << " ";
    }

    cout << "\nTotal Seek Time (SSTF): " << seek_time << endl;
}

void scan(vector<int> requests, int head, int disk_size) {
    vector<int> left, right;
    int seek_time = 0;
    int current = head;
    for (int req : requests) {
        if (req < head)
            left.push_back(req);
        else
            right.push_back(req);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    cout << "\nSCAN Order: ";
    for (int r : right) {
        cout << r << " ";
        seek_time += abs(current - r);
        current = r;
    }
    if (current != disk_size - 1) {
        seek_time += abs(current - (disk_size - 1));
        current = disk_size - 1;
    }
    for (int i = left.size() - 1; i >= 0; --i) {
        cout << left[i] << " ";
        seek_time += abs(current - left[i]);
        current = left[i];
    }
    cout << "\nTotal Seek Time (SCAN): " << seek_time << endl;
}

void c_scan(vector<int> requests, int head, int disk_size) {
    vector<int> left, right;
    int seek_time = 0;
    int current = head;
    for (int req : requests) {
        if (req < head)
            left.push_back(req);
        else
            right.push_back(req);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    cout << "\nC-SCAN Order: ";
    for (int r : right) {
        cout << r << " ";
        seek_time += abs(current - r);
        current = r;
    }
    if (current != disk_size - 1) {
        seek_time += abs(current - (disk_size - 1));
        current = disk_size - 1;
    }
    seek_time += disk_size - 1;
    current = 0;
    for (int l : left) {
        cout << l << " ";
        seek_time += abs(current - l);
        current = l;
    }
    cout << "\nTotal Seek Time (C-SCAN): " << seek_time << endl;
}

int main() {
    int n, head, disk_size;
    vector<int> requests;
    cout << "Enter number of requests: ";
    cin >> n;
    requests.resize(n);
    cout << "Enter the requests: ";
    for (int i = 0; i < n; ++i)
        cin >> requests[i];
    cout << "Enter initial head position: ";
    cin >> head;
    cout << "Enter disk size: ";
    cin >> disk_size;
    fifo(requests, head);
    sstf(requests, head);
    scan(requests, head, disk_size);
    c_scan(requests, head, disk_size);

    return 0;
}
