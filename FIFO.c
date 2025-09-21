#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 10

void fifo(int pages[], int n, int capacity) {
    int frame[capacity], queue[capacity];
    int front = 0, rear = 0;
    int page_faults = 0;
    bool found;

    for (int i = 0; i < capacity; i++) frame[i] = -1;

    printf("FIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        found = false;
        // Check if page is already in a frame
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == pages[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            // Page Fault occurred
            if (rear < capacity) {
                frame[rear] = pages[i];
                queue[rear] = pages[i];
                rear++;
            } else {
                // Replace the oldest page (at front of queue)
                int to_replace = queue[front];
                for (int j = 0; j < capacity; j++) {
                    if (frame[j] == to_replace) {
                        frame[j] = pages[i];
                        break;
                    }
                }
                // Update the queue: remove front, add new page to rear
                for (int j = 0; j < capacity - 1; j++) {
                    queue[j] = queue[j+1];
                }
                queue[capacity-1] = pages[i];
            }
            page_faults++;
            // Print current frame state
            printf("Page %d -> Frames: [", pages[i]);
            for (int j = 0; j < capacity; j++) {
                if (frame[j] != -1) printf(" %d", frame[j]);
                else printf(" -");
            }
            printf(" ] (Page Fault)\n");
        } else {
            printf("Page %d -> Hit\n", pages[i]);
        }
    }
    printf("Total Page Faults (FIFO): %d\n\n", page_faults);
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    fifo(pages, n, capacity);
    return 0;
}