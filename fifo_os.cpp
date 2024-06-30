#include <stdio.h>

// Function prototypes
void fifoPageReplacement();
void fcfsProcessScheduling();

int main() {
    int choice;

    // Display menu and take user input
    printf("Choose an option:\n");
    printf("1. FIFO Page Replacement Algorithm\n");
    printf("2. FCFS Process Scheduling Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fifoPageReplacement();
            break;
        case 2:
            fcfsProcessScheduling();
            break;
        default:
            printf("Invalid choice. Exiting...\n");
    }

    return 0;
}

// Function definitions

void fifoPageReplacement() {
    int i, j, n, ref_str[50], frame[10], no, k, avail, fcount = 0;

    printf("\n ENTER THE NUMBER OF PAGES:\n");
    scanf("%d", &n);

    printf("\n ENTER THE PAGE NUMBER :\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &ref_str[i]);

    printf("\n ENTER THE NUMBER OF FRAMES :");
    scanf("%d", &no);

    for (i = 0; i < no; i++)
        frame[i] = -1;

    j = 0;

    printf("\n ref string  \t page frames     \tHit/Fault\n");
    for (i = 1; i <= n; i++) {
        printf("%d\t\t", ref_str[i]);
        avail = 0;
        for (k = 0; k < no; k++) {
            if (frame[k] == ref_str[i]) {
                avail = 1;
                for (k = 0; k < no; k++)
                    printf("%d\t", frame[k]);
                printf("H");
            }
        }

        if (avail == 0) {
            frame[j] = ref_str[i];
            j = (j + 1) % no;
            fcount++;
            for (k = 0; k < no; k++)
                printf("%d\t", frame[k]);
            printf("F");
        }
        printf("\n");
    }

    printf("Page Fault Is %d\n", fcount);
}

void fcfsProcessScheduling() {
    int i, n, bt[20], wt[20], tat[20];

    printf("\nEnter total number of processes(maximum 20):");
    scanf("%d", &n);

    printf("\nEnter Process Burst Time\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]:", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0; // Waiting time for first process is 0

    // Calculating waiting time
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (int j = 0; j < i; j++)
            wt[i] += bt[j];
    }

    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time");

    // Calculating turnaround time and displaying results
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d", i + 1, bt[i], wt[i], tat[i]);
    }

    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\n\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
}

