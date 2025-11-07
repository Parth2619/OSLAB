#include <stdio.h>

int main() {
    int n, i, j;
    printf("SJF CPU Scheduling\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], wt[n], tat[n], p[n], done[n];
    
    // Input
    for (i = 0; i < n; i++) {
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        p[i] = i + 1;
        done[i] = 0;
    }

    // SJF Scheduling
    int time = 0, count = 0;
    while (count < n) {
        int min = -1, minbt = 9999;
        
        // Find shortest job among arrived processes
        for (i = 0; i < n; i++) {
            if (at[i] <= time && done[i] == 0 && bt[i] < minbt) {
                minbt = bt[i];
                min = i;
            }
        }
        
        if (min == -1) {
            time++;
        } else {
            wt[min] = time - at[min];
            time += bt[min];
            tat[min] = wt[min] + bt[min];
            done[min] = 1;
            count++;
        }
    }

    // Display
    printf("\nP\tAT\tBT\tWT\tTAT\n");
    float twt = 0, ttat = 0;
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i], at[i], bt[i], wt[i], tat[i]);
        twt += wt[i];
        ttat += tat[i];
    }
    
    printf("\nAvg WT: %.2f\n", twt / n);
    printf("Avg TAT: %.2f\n", ttat / n);
    return 0;
}
