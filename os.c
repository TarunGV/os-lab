#include <stdio.h>

int main() {
    int n;
    printf("enter number of processes: ");
    scanf("%d", &n);

    int at[n];
    int bt[n];
    int ct[n];
    int tat[n];
    int wt[n];

    printf("enter arrival times for each process: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("enter burst times for each process: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += bt[i];
        ct[i] = sum;
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
    }

    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
    }

    float avg_ct = 0, avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_ct += ct[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_ct /= n;
    avg_tat /= n;

    printf("Average Completion Time: %.2f\nAverage Turnaround Time: %.2f\nAverage Waiting Time: %.2f",
           avg_ct, avg_tat, avg_wt);

}
