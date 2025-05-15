#include <stdio.h>

int main() {
    int n, m, i, j, k;
    printf("Enter number of processes and resources:\n");
    scanf("%d %d", &n, &m);

    int alloc[n][m], req[n][m], avail[m], finish[n];

    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter request matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &req[i][j]);

    printf("Enter available matrix:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for (i = 0; i < n; i++)
        finish[i] = 0;

    int done;
    do {
        done = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canFinish = 1;
                for (j = 0; j < m; j++) {
                    if (req[i][j] > avail[j]) {
                        canFinish = 0;
                        break;
                    }
                }
                if (canFinish) {
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    finish[i] = 1;
                    done = 1;
                    printf("Process %d can finish.\n", i);
                }
            }
        }
    } while (done);

    int deadlock = 0;
    for (i = 0; i < n; i++)
        if (finish[i] == 0)
            deadlock = 1;

    if (deadlock)
        printf("System is in a deadlock state.\n");
    else
        printf("System is not in a deadlock state.\n");

    return 0;
}

