//1271번 엄청난 부자2
//입력 : 최백준 조교가 가진 돈n과 돈을 받으러온 생명체의 수m이 주어진다.
//첫째 줄에 생명체 하나에게 돌아가는 돈의 양 출력, 두 번째 줄에는 1원씩 분배할 수 없는 남는 돈을 출력


#include <iostream>
using namespace std;

int main(){

    long long n, m;
    n = 0;
    m = 0;
    cin >> n >> m;
    int result_A = n/m;
    int result_B = n%m;

    
    
    cout << result_A << result_B<< endl;
    return 0;






}