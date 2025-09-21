#include<stdio.h>

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], p[n], wt[n], tat[n];
    printf("Enter the burst time for each process:\n");
    for(int i=0; i<n; i++){
        printf("P[%d]: ", i+1);
        scanf("%d", &bt[i]);
        p[i] = i+1; // Process ID
    }

    // Sorting processes based on burst time (Bubble Sort)
    int temp, pos;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(bt[j] < bt[i]){
                // Swap burst time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process id
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculating Waiting Time
    wt[0] = 0;
    for(int i=1; i<n; i++){
        wt[i] = wt[i-1] + bt[i-1];
    }

    // Calculating Turnaround Time
    for(int i=0; i<n; i++){
        tat[i] = bt[i] + wt[i];
    }

    // Displaying Results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(int i=0; i<n; i++){
        printf("P[%d]\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    // Calculating Averages
    float total_wt = 0, total_tat = 0;
    for(int i=0; i<n; i++){
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);

    return 0;
}