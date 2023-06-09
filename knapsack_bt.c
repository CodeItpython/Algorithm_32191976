#include <stdio.h>

int n, W, maxprofit;  //아이템, 용량 및 최대 이익을 저장하기 위한 변수
//w[100]은 항목의 weight를 저장하는 배열
//p[100]은 아이템의 profit을 나타내는 배열
//x[100]은 선택한 항목을 나타내는 정수배열
//bestx[100]은 찾은 최상의 솔루션을 나타내는 배열
int w[100], p[100], x[100], bestx[100];  

void knapsack_bt(int i)
{
    if(i > n)  //모든 항목 고려
    {
        int j;
        int totweight = 0;  // selected items의 총 weight
        int totprofit = 0;  // selected items의 총 profit
        
        for(j=1; j<=n; j++)
        {
            if(x[j])  // item이 선택됐는지 체크
            {
                totweight += w[j];  // selected item의 weight를 더함
                totprofit += p[j];  // selected item의 profit을 더함
            }
        }

        if(totweight <= W && totprofit > maxprofit)  // solution이 맞고, profit이 적합한지 확인
        {
            maxprofit = totprofit;  // maxprofit 업데이트
            for(j=1; j<=n; j++)
                bestx[j] = x[j];  // best solution 업데이트
        }
    }
    else
    {
        x[i] = 0;  // 현재 item 제와
        knapsack_bt(i+1);  // 제외된 항목들로 반복
        x[i] = 1;  // 현재 item 포함
        knapsack_bt(i+1);  // 포함된 항목들로 반복
    }
}


int main()
{
    int i;
    printf("Enter the number of items: ");
    scanf("%d", &n);  // item의 개수를 입력받음
    printf("Enter the capacity of knapsack: ");
    scanf("%d", &W);  // capacity(무게)를 입력받음
    printf("Enter the weight and profit of each item:\n");

    for(i=1; i<=n; i++)
    {
        printf("Item %d: ", i);
        scanf("%d %d", &w[i], &p[i]);  //weight과 profit을 각각 입력받음
    }

    // Using Backtracking
    printf("Using Backtracking:\n");
    maxprofit = 0;  // maxprofit 초기화
    knapsack_bt(1);  // 첫번째 item으로 시작
    printf("Maximum profit = %d\n", maxprofit); //maxprofit 출력
    printf("Selected items: ");
    for(i=1; i<=n; i++)
    {
        if(bestx[i])  //best solution에서 item이 선택됐는지 확인
            printf("%d ", i);  // item들의 index를 출력
    }
    printf("\n");


    return 0;
}
