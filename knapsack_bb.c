#include <stdio.h>

int n, W, maxprofit; //아이템, 용량 및 최대 이익을 저장하기 위한 변수
//w[100]은 항목의 weight를 저장하는 배열
//p[100]은 아이템의 profit을 나타내는 배열
//x[100]은 선택한 항목을 나타내는 정수배열
//bestx[100]은 찾은 최상의 솔루션을 나타내는 배열
int w[100], p[100], x[100], bestx[100];


void knapsack_bb(int i, int weight, int profit) {
    if (weight <= W && profit > maxprofit) {
        maxprofit = profit;
        for (int j = 1; j <= n; j++) {
            bestx[j] = x[j];  // best solution 업데이트
        }
    }

    if (i <= n && weight + w[i] <= W) {
        x[i] = 1;  // 현재 항목 포함
        knapsack_bb(i + 1, weight + w[i], profit + p[i]);  //포함된 항목과 함께 반복
        x[i] = 0;  // 현재 항목 제외
        knapsack_bb(i + 1, weight, profit);  // 제외된 항목으로 반복
    }

    int j;
    int totweight = weight;
    float bound = profit;
    float unit;

    // 나머지 항목을 사용하여 상한 계산
    for (j = i + 1; j <= n; j++) {
        if (totweight + w[j] <= W) {
            totweight += w[j];
            bound += p[j];
        } else {
            unit = (float)(W - totweight) / w[j];  //적합한 항목의 부분 계산
            bound += unit * p[j];  //이익 부분을 한계에 더함
            break;
        }
    }

    //한도가 현재의 최대 이익보다 클 경우 추가로 탐색
    if (bound > maxprofit) {
        x[i] = 0;  // 현재 항목 제외
        knapsack_bb(i + 1, weight, profit);  //제외된 항목으로 반복
    }
}

int main() {
    int i;
    printf("Enter the number of items: ");  //아이템들의 수를 입력
    scanf("%d", &n);
    printf("Enter the capacity of knapsack: "); //capacity(무게)입력
    scanf("%d", &W);
    printf("Enter the weight and profit of each item:\n");

    for (i = 1; i <= n; i++) {
        printf("Item %d: ", i);
        scanf("%d %d", &w[i], &p[i]);  //weight와 profit을 각각 입력받음
    }

    // Branch and Bound 이용
    printf("Using Branch and Bound:\n");
    maxprofit = 0;  // maxprofit 초기화
    knapsack_bb(0, 0, 0);  //아이템이 없는상태를 포함시킴
    printf("Maximum profit = %d\n", maxprofit); //maxprofit 출력
    printf("Selected items: ");
    int flag = 0;
    for (i = 1; i <= n; i++) {
        if (bestx[i]) {  //아이템이 best solution에 있을경우
            if (flag)   //출력이 안나오는 문제로인한 flag변수 설정
                printf(", ");
            printf("%d", i);  //선택된 아이템들을 출력
            flag = 1;
        }
    }
    printf("\n");

    return 0;
}
