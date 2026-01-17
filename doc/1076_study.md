##1076번
변수가 어디서 선언되었는 가에 따라 사용 가능한 범위가 결정된다.
void function() {
    int x = 10;

    if(조건) {
        int y = 20;
    } //y는 여기서 소멸
    cout << y << endl; => 에러 y는 이미 사라짐
    }

#타입 불일치
string color1 = "red",
int value1;
color1 = 5; //에러 string에 int 대입 불가
value1 = color1; //에러 int에 string 대입 불가

#큰 수 처리(long long)
- 오버플로우 문제
int result; // -2,147,483,648 ~ 2,147,483,647
result = 99*1000000000; //오버플로우 따라서 long long result; 로 해야한다.

#거듭 제곱 계산(pow함수)
#include <cmath>

long long result = pow(10,n); //10^n
같은 표현
long long muliplier = 1;
for (int i = 0; i a<n; i++){
    multiplier *=10;
}

#배열 탐색과 매칭
인덱스 = 값 설계
string color[10] = {"black","brown","red",...};
// 인덱스               1       2       3 ...
선형 탐색
for (int i =0;i <10;i++){
    if(입력값 == color[i]){
        저장변수 = i;
        break;
    }
}

8. ✅ 핵심 체크리스트
문제를 풀 때 꼭 확인할 것:

 변수를 어디서 선언해야 하는가? (스코프)
 각 변수의 타입이 적절한가?
 계산 결과가 오버플로우 날 수 있는가?
 문자열과 숫자를 혼용하지 않았는가?
 거듭제곱 계산이 정확한가?