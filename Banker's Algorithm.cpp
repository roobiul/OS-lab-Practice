#include <iostream>
using namespace std;

const int P = 5; // Number of processes
const int R = 3; // Number of resources

int main() {
    // Given Data
    int alloc[P][R] = { {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2} };
    int maxm[P][R] = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3} };
    int avail[R] = {3, 3, 2};

    int need[P][R];
    // Calculate Need Matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];

    int f[P] = {0}; // Finish array, initialized to 0 (false)
    int ans[P], ind = 0; // Safe sequence

    int work[R];
    for (int i = 0; i < R; i++) work[i] = avail[i]; // Initialize work = available

    // Find a safe sequence
    for (int count = 0; count < P; count++) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (f[i] == 0) { // Process not finished
                int j;
                for (j = 0; j < R; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == R) { // Need <= Work for all resources
                    for (int k = 0; k < R; k++)
                        work[k] += alloc[i][k]; // Work = Work + Allocation[i]
                    f[i] = 1;
                    ans[ind++] = i;
                    found = 1;
                }
            }
        }
        if (found == 0) { // No process found that can be satisfied
            cout << "System is not in a safe state!" << endl;
            break;
        }
    }

    // System is safe
    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < P - 1; i++)
        cout << "P" << ans[i] << " -> ";
    cout << "P" << ans[P-1] << endl;

    return 0;
}