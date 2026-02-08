//1110번 문제
//0보다 크거나 같고 99보다 작거나 같은 정수가 주어질때 다음과 같은 연산
//1. 주어진 수가 10보다 작으면 앞에 0을 붙여 두자리 수로 만들기
//2. 각 자리의 숫자를 더한다
//3. 주어진 수의 가장 오른쪽 자리 숫자와 2에서 구한 합의 가장 오른쪽 자리 숫자를 이어 붙이면 새로운 수를 만들 수 있다
//4. 원래 수가 다시 나올때까지 위의 과정을 반복한다
//N이 주어졌을때 N이 몇번째 사이클에 처음 수로 돌아오는지 구하는 프로그램 작성

#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    int start_num = N;
    int Next_num = 0;
    int return_num = 0;

    // 나머지*10 + (몫 + 나머지)의 나머지 = Next_num
    //최종 출력은 사이클 값
    do {
        int a = start_num /10;
        int b = start_num % 10;
        Next_num = (b *10) + (a + b)%10;
        int current_num = Next_num;
        start_num = current_num;
        return_num++;




    } while(N != Next_num); //임베디드1. Yoda condition 상수를 왼쪽에 쓰는 습관

    cout << return_num;
    return 0;




}
//do-while문은 일단 한 번 실행한 뒤에 더할까?를 물어보는 후불제 방식
// - 최소 1회 실행 보장 : 조건이 처음부터 거짓이더라도, 몸체안의 코드는 무저건 한 번은 실행된다
// - 반복 횟수 미정 : 반복 횟수가 사전에 정해져 있지 않고, 조건에 따라 달라질 때 유용하다
// - 세미클론 주의 : while뒤에 반드시 세미클론을 붙여야 한다.