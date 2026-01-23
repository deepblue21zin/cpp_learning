//1284번 문제-구현
//숫자와 숫자 사이 여백이 있어야 한다.
//규칙
//1. 각 숫자 사이에는 1cm여백이 들어간다
//2. 1은 2cm의 너비를 차지해야 한다. 0은 4cm의 너비를 차지해야한다. 나머지 숫자는 모두 3cm의 너비를 차지한다.
//3. 호수판의 경계와 숫자 사이에는 1cm의 여백이 들어가야 한다.

#include <iostream>
using namespace std;

int main(){

    int N;
    
    //N>0를 조건으로 while문 돌리면 계속 반복하면서 10으로 나눠서 자릿수를 하나씩 뽑을 수 있고 그걸 if문으로 비교하면 된다.
    while(true){

    
        cin >> N;
        if(N == 0) break;
        int total_length = 1;
    
        while(N>0){
            
        
            int alpha = N%10;
            if (alpha == 1){
                total_length += 2;

            }else if(alpha == 0){
                total_length += 4;
            }else{
                total_length +=3;
        
            }
            total_length += 1;
            N = N/10;

            
        }
        cout << total_length << endl;
        
        


    }
    return 0;
   
        
        
    

    //if를 이용해서 1은 2cm, 0은 4cm, 나머지 숫자는 3cm로 설정.
    //total_length = 2 + if문 결과'
    //while로 반복하기(N=0전까지 반복0)
    //0이 아니면 계속 입력을 받게 만들어야 하는데 그래서 while문이 2개를 해야한다.




}

//=은 대입이다. ==이 비교이다
//수학 계산 우선순위를 정할 때는 반드시 소괄호만 써야한다.중괄호는 코드 블록을 만들 때 쓴다.
/*// 예: N = 5300
int total_length = 1; // 맨 앞 여백 1cm 포함 (문제 조건에 따라 조정)

while (N > 0) {
    int digit = N % 10; // 1. 맨 끝자리(일의 자리)를 뽑음. (5300 -> 0)
    
    // 여기서 digit이 1인지, 0인지, 나머지인지에 따라 길이를 더함
    if (digit == 1) total_length += 2;
    else if (digit == 0) total_length += 4;
    else total_length += 3;
    
    total_length += 1; // 숫자 사이 여백 1cm
    
    N = N / 10; // 2. 맨 끝자리를 버림. (5300 -> 530 -> 53 -> 5 -> 0)
}
// 루프가 끝나면 total_length 출력*/

//문제1 : while(N > 0)내부에서 N을 줄여주는 코드가 없다 => 120을 입력하면 영원히 120인 상태로 계속 돈다.
//문제2 : while(N==0) => 입력 받기 전에는 while 조건에 N을 쓰면 안된다. 일단 무조건 반복하고 입력받은 뒤에 0이면 탈출하는 구조로 만들어야 한다.
// 이유 : N에 값이 안들어가 있는데 비교부터 하면 에러가 발생