//10818번 문제 최소 최대
//N개의 정수가 주어진다면 이때 최소 최대값을 구하는 프로그램 작성
//입력 정수의 개수 N, 둘째 줄에 N개의 정수 공백으로 구분해서 주어진다
//출력 ㅜ개의 정수중 최솟값과 최댓값 구분 출력

#include <iostream>
#include <climits>
using namespace std;

int main() {
    int N;
    cin >> N;

    int min_value = 1000001; //0으로 초기화하게 되는 경우 입력되는 숫자가 0 보다크면 min_value = 0이된다.
    int max_value = -1000001;
    int input_value = 0;

    for (int i=0;i<N;i++){
        cin >> input_value;

        if (i==0){
            min_value = input_value;
            max_value = input_value;
        } else{
            if (min_value > input_value){
                min_value = input_value;
            }
            if (max_value < input_value){
                max_value = input_value;
            }


        }

        }
        cout << min_value << " " << max_value << endl;
        return 0;


}