#include <stdio.h>

int main() {
    int n, tq, i, time = 0, remaining;
    printf("Round Robin CPU Scheduling Algorithm\n");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], rt[n], wt[n], tat[n], at[n];
    for (i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &at[i]);
        rt[i] = bt[i]; // remaining time
        wt[i] = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    remaining = n;
    int complete[n];
    for (i = 0; i < n; i++) complete[i] = 0;

    while (remaining > 0) {
        int done = 1;
        for (i = 0; i < n; i++) {
            // only schedule if process has arrived and has remaining time
            if (rt[i] > 0 && at[i] <= time) {
                done = 0;
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    // waiting time = finish time - arrival - burst
                    wt[i] = time - at[i] - bt[i];
                    if (wt[i] < 0) wt[i] = 0;
                    rt[i] = 0;
                    remaining--;
                }
            }
        }
        if (done) {
            // no process was ready at current time: jump to next arrival
            int min_at = 1000000000;
            for (i = 0; i < n; i++) {
                if (rt[i] > 0 && at[i] > time && at[i] < min_at) {
                    min_at = at[i];
                }
            }
            if (min_at != 1000000000) {
                time = min_at;
            }
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    float total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
