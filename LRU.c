#include <stdio.h>
#include <stdbool.h>

void lru(int pages[], int n, int capacity) {
    int frames[capacity];
    int counter[capacity]; // Tracks how recently a page was used (lower = older)
    int page_faults = 0;
    bool found;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }

    printf("LRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        found = false;
        // Check for page hit
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                counter[j] = i + 1; // Update usage time to current step
                break;
            }
        }

        if (!found) {
            // Page Fault occurred, find LRU page to replace
            int lru_index = 0;
            int min_counter = counter[0];
            for (int j = 1; j < capacity; j++) {
                if (counter[j] < min_counter) {
                    min_counter = counter[j];
                    lru_index = j;
                }
            }
            // Replace the LRU page
            frames[lru_index] = pages[i];
            counter[lru_index] = i + 1; // Set its usage time
            page_faults++;

            // Print current frame state
            printf("Page %d -> Frames: [", pages[i]);
            for (int j = 0; j < capacity; j++) {
                if (frames[j] != -1) printf(" %d", frames[j]);
                else printf(" -");
            }
            printf(" ] (Page Fault)\n");
        } else {
            printf("Page %d -> Hit\n", pages[i]);
        }
    }
    printf("Total Page Faults (LRU): %d\n", page_faults);
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    lru(pages, n, capacity);
    return 0;
}