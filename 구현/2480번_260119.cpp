//주사위 세개
//1~6까지 숫자가 적힌 주사위 3개를 던졌을 때,
// 1. 같은 눈이 3개 나오면 10000원+(같은 눈)×1000원의 상금을 받게 된다.
// 2. 같은 눈이 2개 나오면 1000원+(같은 눈)×100원의 상금을 받게 된다.
// 3. 모두 다른 눈이 나오면 (그 중 가장 큰 눈)×100원의 상금을 받게 된다.
//예를 들어, 3개의 눈이 3, 3, 6 이면 1000+3×100=1300원을 받게 된다.
//3개의 눈이 2, 2, 2 이면 10000+2×1000=12000원을 받게 된다.
//3개의 눈이 6, 2, 5 이면 가장 큰 눈이 6이므로 6×100=600원을 받게 된다.
//3개의 눈이 주어졌을 때, 상금을 계산하는 프로그램을 작성 하시오.




#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int a, b, c;
    cin >>a >>b >>c;
    if(a==b && b==c){
        cout << 10000 + a*1000;
    }else if(a==b || a==c){
        cout << 1000 + a*100 <<endl;

    }else if(a==b || b==c){
        cout << 1000+b*100 << endl;
    }else if(c==a || c==b){
        cout << 1000+c*100 << endl;
    }else if(a!=b && a!=c &&b!=c){
        int result = max({a, b, c});
        cout << result*100 << endl;
    }
    return 0;

}

//중복 코드가 많아서 리팩토링이 필요해 보임.
//sorting을 이용해서 푸는 방법
/*int dice[3];
for(int i=0; i<3; i++) cin >> dice[i];

sort(dice, dice + 3); // 오름차순 정렬 (dice[0] <= dice[1] <= dice[2])

if (dice[0] == dice[2]) { // 처음과 끝이 같으면 세 숫자 모두 같음
    cout << 10000 + dice[0] * 1000;
}
else if (dice[0] == dice[1] || dice[1] == dice[2]) { // 인접한 숫자만 비교
    cout << 1000 + dice[1] * 100; // 가운데 숫자는 무조건 중복 숫자에 포함됨
}
else {
    cout << dice[2] * 100; // 정렬되었으므로 마지막 숫자가 가장 큼
}*/