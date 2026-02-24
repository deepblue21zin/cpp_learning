//2042 구간 합 구하기 실시간 데이터 스트림 처리나 데이터 베이스 인덱싱의 핵심 원리
//N개의 수가 주어져 있다. 중간에 수의 변경이 번번히 일어나고, 그 중간에 어떤 부분의 합을 구하려한다.
//ex) 1 2 3 4 5, 3->6, 2~5의 합을 구하면 17을 출력. 그 상태에서 다섯 번째 수를 2로 바꾸고 3~5까지 합을 구하라고 하면 12가 된다.
//입력 : 첫째 줄에 수의 개수 N(1~1000000)과 M(1~10000), K(1~10000)가 주어진다.
//M은 수의 변경이 일어나는 횟수, K는 구간의 합을 구하는 횟수. 그리고 둘째 줄부터 N+1번째 줄까지 N개의 수가 주어진다. 그리고 N+2번째 줄부터 M+K+1번째 줄까지 세 개의 정수 a, b, c가 주어진다. a가 1이면 b번째 수를 c로 바꾸라는 뜻이고, a가 2이면 b~c까지의 합을 구하라는 뜻이다.
//출력 : K개의 줄에 걸쳐 구간의 합을 출력한다.


#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
long long tree[4000000]; //세그먼트 트리의 크기는 일반적으로 입력 배열의 크기보다 약 4배 정도로 설정

int main() {

    //for로 매번 합을 구하면 연산량 폭탄 -> 세그먼트 트리로 해결(데이터를 이진 트리 구조로 관리하여, 수정과 합 계산을 모두 O(log N) 시간에 처리할 수 있도록 하는 자료구조)
    
    int N, M, K;
    cin >> N >> M >> K;
    vector<long long> j(N); //입력 배열, long long으로 선언하여 큰 수의 합도 처리할 수 있도록 함
    for (int i=0; i < N;i++){
        cin >> j[i];
    }
    //세그먼트 트리 구축
    for (int i=0; i < N; i++){
        tree[i + N] = j[i]; //리프 노드에 입력 배열의 값 저장
    }  
    for (int i = N - 1; i > 0; i--){
        tree[i] = tree[2 * i] + tree[2 * i + 1]; //내부 노드에 자식 노드의 합 저장
    } 
    //쿼리 처리
    for (int i = 0; i < M + K; i++){
        int a, b;
        long long c;
        cin >> a >> b >> c;
        if (a == 1){
            //수의 변경
            int pos = b + N - 1; //리프 노드의 위치 계산
            tree[pos] = c; //값 변경
            //변경된 값을 반영하여 트리 업데이트
            while (pos > 1){
                pos /= 2; //부모 노드로 이동
                tree[pos] = tree[2 * pos] + tree[2 * pos + 1]; //부모 노드의 값 업데이트
            }
        } else if (a == 2){
            //구간의 합 계산
            long long sum = 0;              
            int left = b + N - 1; //구간의 시작 위치 계산
            long long right = c + N - 1; //구간의 끝 위치 계산
            while (left <= right){
                if (left % 2 == 1){ //왼쪽 노드가 홀수인 경우, 해당 노드의 값을 결과에 더하고 다음 노드로 이동
                    sum += tree[left];
                    left++;

                }
                if (right % 2 == 0){ //오른쪽 노드가 짝수인 경우, 해당 노드의 값을 결과에 더하고 다음 노드로 이동
                    sum += tree[right];
                    right--;
                }
                left /= 2; //부모 노드로 이동
                right /= 2; //부모 노드로 이동
            }
            cout << sum << "\n";
        }

    }
    return 0;





}