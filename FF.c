#include<stdio.h>

int main() {
    int n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    int block_size[n], process[n];
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &block_size[i]);
    }
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &process[i]);
    }

    int allocation[n], total_internal_frag = 0, total_external_frag = 0;
    for (int i = 0; i < n; i++) allocation[i] = -1;

    // First Fit Allocation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (block_size[j] >= process[i] && allocation[i] == -1) {
                allocation[i] = j;
                total_internal_frag += (block_size[j] - process[i]);
                block_size[j] = 0; // Mark block as used
                break;
            }
        }
    }

    // Calculate External Fragmentation (sum of all unused blocks)
    for (int i = 0; i < n; i++) {
        total_external_frag += block_size[i];
    }

    // Display Results
    printf("\nProcess No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i+1, process[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
    printf("Total Internal Fragmentation: %d\n", total_internal_frag);
    printf("Total External Fragmentation: %d\n", total_external_frag);
    return 0;
}