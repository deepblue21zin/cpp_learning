//25304번 문제 영수증
//구매한 각 물건의 가격과 개수, 구매한 물건들의 총 금액 일치하는 지 확인
//입력 : 첫째 줄에는 총금액 X 주어진다, 둘째 줄 : 구매한 물건의 종류의 수 N, 각 물건의 가격a와 b가 공백을 사이에 두고 주어진다.
#include <iostream>
using namespace std;

int main() {

    //입력 : 1<= X <= 1,000,000,000, 1<= N <= 100, 1<= a,b <= 1,000,000
    int X = 0;
    int N = 0, a = 0, b = 0;

    //필요한 변수 : a*b의 합의 결과 값을 저장할 sum변수, 
    long long sum = 0; //초기화
    cin.width(1000000000); //입력받을 수 있는 최대 글자 수 설정(**임베디드)
    cin >> X;
    
    cin.width(100);
    cin >> N;
    const int Max_type = N;
    
    //입력값 a, b는 N의 값만큼 반복해서 입력을 받게 해야함(for문 사용)
    for (int j = 0; j < Max_type; j++){
        cin.width(1000000);
        cin >> a;
        cin.width(10);
        cin >> b;
        printf("%d %d\n", a, b); //입력값 확인용 출력문

        sum += a*b;
    }

    //알고리즘 : 구매한 물건의 총 금액 = X, 구매한 물건의 총 금액 계산 = a*b의 합,
    // 즉 x = a*b의 합이면 Yes, 아니면 No 출력 (if else문 사용)
    
    if (X == sum){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }

    //출력 : 구매한 물건들의 총 금액과 영수증에 적힌 총 금액이 일치하면 Yes, 일치하지 않으면 No 출력

    return 0;
}

//에러사항 : 입력을 계속 받거나, 중간에 No를 출력해버림,