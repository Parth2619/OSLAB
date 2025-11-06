#include <stdio.h>

int main() {
    int n;
    printf("FCFS CPU Scheduling Algorithm\n");
    printf("Enter number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    int bt[n], at[n], wt[n], tat[n], pid[n];
    printf("Enter burst time and arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1; // original process id
        printf("P%d - Burst time: ", pid[i]);
        while (scanf("%d", &bt[i]) != 1) {
            // clear invalid input
            int c; while ((c = getchar()) != EOF && c != '\n');
            printf("Invalid input. Enter integer burst time for P%d: ", pid[i]);
        }
        printf("P%d - Arrival time: ", pid[i]);
        while (scanf("%d", &at[i]) != 1) {
            int c; while ((c = getchar()) != EOF && c != '\n');
            printf("Invalid input. Enter integer arrival time for P%d: ", pid[i]);
        }
    }

    // Sort processes by arrival time (stable selection sort by swapping all arrays)
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (at[j] < at[min])
                min = j;
        }
        if (min != i) {
            int tmp;
            tmp = at[i]; at[i] = at[min]; at[min] = tmp;
            tmp = bt[i]; bt[i] = bt[min]; bt[min] = tmp;
            tmp = pid[i]; pid[i] = pid[min]; pid[min] = tmp;
        }
    }

    int current_time = 0;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < at[i])
            current_time = at[i];
        wt[i] = current_time - at[i];
        current_time += bt[i];
        tat[i] = current_time - at[i];

        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    return 0;
}
