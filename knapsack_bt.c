// 0-1 knapsack 문제를 backtracking과 branch-and-bound 기법으로 구현할 것.
// - C언어를 사용하여 구현
// - 3가지 이상의 입력 데이터로 테스트한 결과를 분석
// - 주요 자료구조와 알고리즘을 구체적으로 설명
// - 소스 파일은 보고서와 별도로 제출 (GitHib 링크 제출 가능)

#include <stdio.h>
#include <stdlib.h>

int n, W, maxprofit;
int w[100], p[100], x[100], bestx[100];


void knapsack_bt(int i)
{
    if(i > n)
    {
        int j;
        int totweight = 0;
        int totprofit = 0;
        
        for(j=1; j<=n; j++)
        {
            if(x[j])
            {
                totweight += w[j];
                totprofit += p[j];
            }
        }

        if(totweight <= W && totprofit > maxprofit)
        {
            maxprofit = totprofit;
            for(j=1; j<=n; j++)
                bestx[j] = x[j];
        }
    }
    else
    {
        x[i] = 0;
        knapsack_bt(i+1);
        x[i] = 1;
        knapsack_bt(i+1);
    }
}


int main()
{
    int i;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the capacity of knapsack: ");
    scanf("%d", &W);
    printf("Enter the weight and profit of each item:\n");

    for(i=1; i<=n; i++)
    {
        printf("Item %d: ", i);
        scanf("%d %d", &w[i], &p[i]);
    }

    // Using Backtracking
    printf("Using Backtracking:\n");
    knapsack_bt(1);
    printf("Maximum profit = %d\n", maxprofit);
    printf("Selected items: ");
    for(i=1; i<=n; i++)
    {
        if(bestx[i])
            printf("%d ", i);
    }
    printf("\n");


    return 0;
}
