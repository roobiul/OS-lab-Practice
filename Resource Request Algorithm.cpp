#include <iostream>
using namespace std;

const int P = 5, R = 3;

// Function to check if the system is in a safe state (from Experiment 8)
bool isSafe(int alloc[P][R], int need[P][R], int avail[R]) {
    int work[R];
    bool finish[P] = {false};
    int safeSeq[P];
    int count = 0;

    for (int i = 0; i < R; i++) work[i] = avail[i];

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += alloc[i][k];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) return false; // System is not in a safe state
    }
    // System is safe (safe sequence exists)
    cout << "System is safe. Safe sequence: ";
    for (int i = 0; i < P; i++) cout << "P" << safeSeq[i] << " ";
    cout << endl;
    return true;
}

int main() {
    // Initial System State
    int alloc[P][R] = {{0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2}};
    int maxm[P][R] = {{7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3}};
    int avail[R] = {3,3,2};

    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];

    // Process P1 makes a request: Request1 = {1, 0, 2}
    int p = 1; // Process index (P1)
    int request[R] = {1, 0, 2};

    cout << "Process P1 requests: {" << request[0] << ", " << request[1] << ", " << request[2] << "}" << endl;

    // Step 1: Check if Request <= Need
    for (int j = 0; j < R; j++) {
        if (request[j] > need[p][j]) {
            cout << "Error: Request exceeds declared maximum need." << endl;
            return 0;
        }
    }

    // Step 2: Check if Request <= Available
    for (int j = 0; j < R; j++) {
        if (request[j] > avail[j]) {
            cout << "Resources not available. Process P1 must wait." << endl;
            return 0;
        }
    }

    // Step 3: Pretend to allocate the resources
    for (int j = 0; j < R; j++) {
        avail[j] -= request[j];
        alloc[p][j] += request[j];
        need[p][j] -= request[j];
    }

    // Step 4: Check if the new state is safe
    if (isSafe(alloc, need, avail)) {
        cout << "Request can be granted. System remains in a safe state." << endl;
        // System state would be updated permanently here
    } else {
        cout << "Request would lead to an unsafe state. Request denied. Process P1 must wait." << endl;
        // Revert the pretended allocation
        for (int j = 0; j < R; j++) {
            avail[j] += request[j];
            alloc[p][j] -= request[j];
            need[p][j] += request[j];
        }
    }
    return 0;
}