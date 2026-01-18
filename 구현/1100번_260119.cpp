#include <iostream>
using namespace std;


int main() {
    //체스판 8x8크기, 흰색칸과 검은칸이 번갈아 배치
    //가장 왼쪽 위칸 (0,0)은 흰색
    //하얀 칸 위에 말이 몇 개 있는 지 구하기
    //. = 빈칸, F = 말이 있는 칸
    //홀수 행은 짝수 열이 하얀 칸
    //짝수 행은 홀수 열이 하얀 칸
    int count = 0;

    for(int i = 0;i < 8; i++){
        if (i%2 == 0){
            for(int j=0; j < 8; j++){
                char a;
                cin >> a;
                if(j%2==0 && a=='F'){
                    count++;

                }
            }
        }

            if(i%2==1){
                for(int j=0; j<8;j++){
                    char a;
                    cin >> a;
                    if(j%2==1 && a=='F'){
                        count++;
                    }
                }
            }
        
    }
    cout << count << endl;
    return 0;
    

}

//https://www.acmicpc.net/problem/1100
//1100번: 하얀 칸
//처음 문제 짝수칸만 스캔하게 설계를 해서 오류
//수정했을경우 행 개수가 맞지 않음 이유? => 괄호의 중요성 짝수if문 안에 홀수if문이 들어가면 안됨
//따라서 if문을 분리해서 각각 8번씩 돌게 수정