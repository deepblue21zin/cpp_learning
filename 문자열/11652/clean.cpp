#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<long long> v;
    v.reserve(static_cast<size_t>(N)); //<=> v.reserve(N);
    //벡터가 내부적으로 확보할 메모리 크기를 size_t로 지정해야 합니다.


    for (int i = 0; i < N; ++i) {
        long long integer;
        cin >> integer;
        v.push_back(integer);
    }

    // 문제 조건상 N >= 1 이지만, 습관적으로 안전하게 처리
    if (v.empty()) {
        return 0;
    }

    sort(v.begin(), v.end());  //정수 정렬은 stable_sort안쓰고 sort써도 된다.

    long long best_value = v[0];
    int best_cnt = 1;
//현재 구간과 best구간을 분리
    long long cur_value = v[0];
    int cur_cnt = 1;

    for (int i = 1; i < N; ++i) {
        if (v[i] == cur_value) {
            ++cur_cnt;
        } else {
            // 구간 종료 -> best 갱신
            if (cur_cnt > best_cnt) {
                best_cnt = cur_cnt;
                best_value = cur_value;
            }
            cur_value = v[i];
            cur_cnt = 1;
        }
    }

    // 마지막 구간 처리
    if (cur_cnt > best_cnt) {
        best_cnt = cur_cnt;
        best_value = cur_value;
    } //best갱신이 한번도 안되는 경우 

    // 동률일 때는 "가장 작은 값"이 정답인데,
    // 정렬 후 첫 등장 값을 유지하므로 (>) 비교만으로 자연스럽게 만족.
    cout << best_value << '\n';
    return 0;
}