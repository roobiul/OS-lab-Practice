#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
//Process Creation with fork() and Sorting
void ascendingSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

void descendingSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
}

int main() {
    int arr[] = {10, 5, 8, 1, 7, 3, 9, 2, 6, 4};
    int n = 10;
    pid_t pid = fork();

    if (pid == 0) { // Child Process
        printf("Child Process - Sorting in Descending Order:\n");
        descendingSort(arr, n);
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    } else { // Parent Process
        printf("Parent Process - Sorting in Ascending Order:\n");
        ascendingSort(arr, n);
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    }
    return 0;
}