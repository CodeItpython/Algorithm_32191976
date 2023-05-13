#include <stdio.h>

int n, W, maxprofit;
int w[100], p[100], x[100], bestx[100];

void knapsack_bb(int i, int weight, int profit) {
    if (weight <= W && profit > maxprofit) {
        maxprofit = profit;
        for (int j = 1; j <= n; j++) {
            bestx[j] = x[j];
        }
    }

    if (i <= n && weight + w[i] <= W) {
        x[i] = 1;
        knapsack_bb(i + 1, weight + w[i], profit + p[i]);
        x[i] = 0;
        knapsack_bb(i + 1, weight, profit);
    }

    int j;
    int totweight = weight;
    float bound = profit;
    float unit;

    for (j = i + 1; j <= n; j++) {
        if (totweight + w[j] <= W) {
            totweight += w[j];
            bound += p[j];
        } else {
            unit = (float)(W - totweight) / w[j];
            bound += unit * p[j];
            break;
        }
    }

    if (bound > maxprofit) {
        x[i] = 0;
        knapsack_bb(i + 1, weight, profit);
    }
}

int main() {
    int i;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the capacity of knapsack: ");
    scanf("%d", &W);
    printf("Enter the weight and profit of each item:\n");

    for (i = 1; i <= n; i++) {
        printf("Item %d: ", i);
        scanf("%d %d", &w[i], &p[i]);
    }

    // Using Branch and Bound
    printf("Using Branch and Bound:\n");
    maxprofit = 0;
    knapsack_bb(0, 0, 0);
    printf("Maximum profit = %d\n", maxprofit);
    printf("Selected items: ");
    int flag = 0;
    for (i = 1; i <= n; i++) {
        if (bestx[i]) {
            if (flag)
                printf(", ");
            printf("%d", i);
            flag = 1;
        }
    }
    printf("\n");

    return 0;
}
