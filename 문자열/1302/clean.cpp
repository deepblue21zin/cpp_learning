#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    unordered_map<string, int> freq;
    //map : 내부가 정렬된 트리 구조(키가 항상 정렬됨) → 탐색/삽입 O(log N)
    //unordered_map : 내부가 해시 테이블(키 정렬 없음) → 평균 탐색/삽입 O(1)
    freq.reserve(static_cast<size_t>(N) * 2); // 리해시 줄이기(경험적)(중요)

    for (int i = 0; i < N; ++i) {
        string book;
        cin >> book;
        ++freq[book]; //값이 필요 없으니 전위 증가로 통일”이라는 스타일/습관에 가깝다.
        //freq[key]는 “없으면 만들어버림”, find()는 “없으면 안 만든다”
    }

    // best 초기화를 "첫 원소"로 확실히 잡아서 동률 비교가 안전하게 동작하게 함
    int best_cnt = -1; //첫 원소를 무조건 채택하기 위해서
    string best_title;

    for (const auto& kv : freq) { //const auto& kv : freq => 복사 비용 없이 안전하게 읽기만 함.
        const string& title = kv.first;
        const int cnt = kv.second;

        if (cnt > best_cnt || (cnt == best_cnt && title < best_title)) {
            best_cnt = cnt;
            best_title = title;
        }
    }

    cout << best_title << '\n';
    return 0;
}