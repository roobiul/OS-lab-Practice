#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
        p[i].completion_time = 0;
    }

    int current_time = 0, completed = 0;
    int prev_selected = -1; // To track context switches for Gantt chart
    printf("\nGantt Chart:\n");

    while (completed < n) {
        int idx = -1;
        int min_remaining = INT_MAX;

        // Find process with minimum remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                if (p[i].remaining_time < min_remaining) {
                    min_remaining = p[i].remaining_time;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            // Print Gantt chart segment if process changes
            if (prev_selected != idx) {
                if (current_time > 0) printf("|");
                printf(" P%d @ %d ", p[idx].pid, current_time);
                prev_selected = idx;
            }

            // Execute the process for 1 unit of time
            p[idx].remaining_time--;
            current_time++;

            // If process is completed
            if (p[idx].remaining_time == 0) {
                completed++;
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            }
        } else {
            // CPU is idle
            if (prev_selected != -1) {
                printf("| IDLE @ %d ", current_time);
                prev_selected = -1;
            }
            current_time++;
        }
    }
    printf("|\n"); // End of Gantt chart

    // Display results
    float total_wt = 0, total_tat = 0;
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}