//3273번 두 수의 합
/*리팩터 순서 고정:

디버그 출력 정리(게이트 유지 가능)

함수 2개로 분리

count_pairs_two_pointers(sorted array, x)

read_input()는 main에 두거나 별도

자료구조를 명확히:

임베디드 감각으로는 static int a[MAX_N];가 가장 예측 가능

포트폴리오에서는 vector<int>도 OK인데, “왜 OK인지”를 notes에 써야 함

주석 2줄: “왜 투포인터” + “복잡도/RAM”*/

#include <algorithm>
#include <iostream>
#include <vector>

static int count_pairs_two_pointers(std::vector<int>& a, const int x) {
    std::sort(a.begin(), a.end());

    int left = 0;
    int right = static_cast<int>(a.size()) - 1; //a.size 는 size_t(부호 없는 정수)이므로, int로 변환하여 right에 할당
    int pair = 0;

    while (left < right) {
        const int s = a[left] + a[right];
        if (s < x) {
            ++left;
        } else if (s > x) {
            --right;
        } else {
            ++pair;
            ++left;
            --right;
        }
    }
    return pair;
}//함수 분리 (입력/출력 과 해결로직이 분리됨)

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); //입력 속도 최적화

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<int> a; //vector<int>는 동적 배열로, 입력 크기에 따라 자동으로 크기가 조절됨. 재할당이 발생할 수 있지만, 일반적으로 효율적임.
    a.reserve(n); // 재할당 최소화(성능/예측성) -> 동적할당을 쓰되 예측 가능하게 만듦
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        a.push_back(v);
    }
    int x;
    std::cin >> x;

    // Time: O(N log N), RAM: O(N)
    std::cout << count_pairs_two_pointers(a, x) << "\n";
    return 0;
}
