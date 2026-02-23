//3273번 단어 공부
//1. 큰 버퍼 로컬 금지 -> static/global
//2. 자료형 최악값 기준
//3. 디버그 출력 매크로

//n개의 서로 다른 양의 정수 a1, a2, ...an으로 이루어진 수열. 
//1<= ai <= 1,000,000 자연수.
//ai + aj = x(1<= i < j <= n)인 쌍의 개수 구하기

#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int a[100005]; //수열의 최대 크기 100,000이므로 100,005로 선언(*수정)
//큰 버퍼 로컬 금지
#ifdef DEBUG
  #define DBG(...) do { fprintf(stderr, __VA_ARGS__); } while(0)
#else
  #define DBG(...) do {} while(0)
#endif
int main() {

    //입력 수열의 크기 n과 수열에 포함되는 수, X가 주어진다. 1<= n <= 100,000, 1 <= X <= 2,000,000
    //변수 설정 : n, x, size of sequence, pairs, 
    int n;
    int x;  


    ios_base::sync_with_stdio(false);
    cin.tie(NULL);//산업용 : 입출력 속도 향상(*수정)
    if (!(cin >> n)){
        return 0;
    }
    int size_sequence = n;
    
    for (int k = 0; k < size_sequence; k++){
        cin >> a[k];
    }
    
    cin >> x;


    //로직 : 일단 i < j이므로, i는 0부터 n-2개, j는 i+1부터 n-1까지 반복문 돌리기
    //ai + aj = x
    /*for (int i = 0; i < size_sequence - 1; i++){
        for (int j = i + 1; j < size_sequence; j++){
            if (a[i] + a[j] == x){
                pair++;
            }
        }
    }*/
    
    //입력 최대 100000이므로 for문을 돌면 100억번의 연산을 수행, 보통 1억번 내외로 해야한다.
    sort(a, a + size_sequence); //오름차순 정렬
    int left = 0;
    int right = size_sequence - 1;
    int pair = 0;

    while (left < right){
        int sum = a[left] + a[right];
        DBG("[DBG] left=%d right=%d a[left]=%d a[right]=%d sum=%d\n", left, right, a[left], a[right], sum);

        if (sum == x){
            pair++;
            left++;
            right--;
        }else if(sum <x){
            left++;
        }else{
            right--;
        }
        
    }

    //출력 쌍의 개수(ai + aj = x)
    cout << pair << "\n";
    return 0;

}

//핵심 투포인터 기법 : 정렬된 데이터에서 두 수의 합을 찾을 때 사용하는 아주 효율적인 기술이다. 
//1. 오름차순으로 정렬, 2. 두개의 포인터 만들기, 3. 좁혀오기