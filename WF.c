#include<stdio.h>

int main() {
    int n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    int block_size[n], process[n];
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < n; i++) scanf("%d", &block_size[i]);
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) scanf("%d", &process[i]);

    int allocation[n], total_internal_frag = 0, total_external_frag = 0;
    for (int i = 0; i < n; i++) allocation[i] = -1;

    // Worst Fit Allocation
    for (int i = 0; i < n; i++) {
        int worst_idx = -1;
        for (int j = 0; j < n; j++) {
            if (block_size[j] >= process[i]) {
                if (worst_idx == -1 || block_size[j] > block_size[worst_idx]) {
                    worst_idx = j;
                }
            }
        }
        if (worst_idx != -1) {
            allocation[i] = worst_idx;
            total_internal_frag += (block_size[worst_idx] - process[i]);
            block_size[worst_idx] = 0; // Mark block as used
        }
    }

    for (int i = 0; i < n; i++) total_external_frag += block_size[i];

    printf("\nProcess No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, process[i]);
        (allocation[i] != -1) ? printf("%d\n", allocation[i]+1) : printf("Not Allocated\n");
    }
    printf("Total Internal Fragmentation: %d\n", total_internal_frag);
    printf("Total External Fragmentation: %d\n", total_external_frag);
    return 0;
}