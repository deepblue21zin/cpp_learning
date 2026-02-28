//11723번 집합 문제
//비어있는 공집합 S가 주어졌을때 아래 연산을 수행하는 프로그램 작성
/*add x: S에 x를 추가한다. (1 ≤ x ≤ 20) S에 x가 이미 있는 경우에는 연산을 무시한다.
remove x: S에서 x를 제거한다. (1 ≤ x ≤ 20) S에 x가 없는 경우에는 연산을 무시한다.
check x: S에 x가 있으면 1을, 없으면 0을 출력한다. (1 ≤ x ≤ 20)
toggle x: S에 x가 있으면 x를 제거하고, 없으면 x를 추가한다. (1 ≤ x ≤ 20)
all: S를 {1, 2, ..., 20} 으로 바꾼다.
empty: S를 공집합으로 바꾼다.*/

//입력 : 첫줄에 수행해야하는 연산의 수 M(1<= M <= 3,000,000)
//두번째 줄부터 M개의 줄에 수행해야 하는 연산이 한줄에 하나씩 주어진다.
//출력 : check 연산이 주어질때마다 결과 출력

#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

#ifdef DEBUG
  #define DLOG(msg) do { cerr << msg << '\n'; } while (0)
#else
  #define DLOG(msg) do {} while (0)
#endif

void processCommand(string cmd, int x, uint32_t &S){
    if (cmd == "add"){
        S |= (1 << (x-1));
    }else if(cmd == "remove"){
        S &= ~(1 << (x-1));
    }else if(cmd == "check"){
        cout << ((S & (1 << (x-1))) ? 1 : 0) << "\n";
    }else if(cmd == "toggle"){
        S ^= ( 1<< (x-1));
    }else if (cmd == "all"){
        S = (1 << 20) - 1;
    }else if(cmd == "empty"){
        S = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //입력 : M 입력 및 for문 연산 입력
    uint32_t M;
    cin >> M;
    uint32_t S = 0;


    while(M--){
        string cmd;
        int x = 0;
        cin >> cmd;
        if (cmd == "add" || cmd == "remove" || cmd == "check" || cmd == "toggle") {
            cin >> x;
        }
        processCommand(cmd, x, S);

    }

    return 0;
}