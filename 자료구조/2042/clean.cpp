#include <iostream>
#include <vector>

using namespace std;

// 전역 상수로 관리 (가독성 및 유지보수)
const int MAX_N = 1000000;
long long tree[2097152]; // 2^21 (100만보다 큰 2의 거듭제곱 반영)

int main() {
    // 1. 입출력 병목 제거
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;

    // 2. N보다 큰 최소 2의 거듭제곱 S 구하기 (비재귀 트리의 핵심)
    int S = 1;
    while (S < N) S <<= 1;

    // 3. 리프 노드 입력
    for (int i = 0; i < N; i++) {
        cin >> tree[S + i];
    }

    // 4. 트리 빌드 (Bottom-up)
    for (int i = S - 1; i > 0; i--) {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }

    // 5. 실시간 데이터 처리
    for (int i = 0; i < M + K; i++) {
        long long type, b, c;
        cin >> type >> b >> c;

        if (type == 1) { // Update
            int pos = S + (int)b - 1;
            tree[pos] = c;
            while (pos > 1) {
                pos >>= 1; // Bit shift가 /2보다 임베디드에서 선호됨
                tree[pos] = tree[pos << 1] + tree[(pos << 1) | 1];
            }
        } else { // Query
            long long sum = 0;
            int left = S + (int)b - 1;
            int right = S + (int)c - 1;

            while (left <= right) {
                if (left % 2 == 1) sum += tree[left++];
                if (right % 2 == 0) sum += tree[right--];
                left >>= 1; right >>= 1;
            }
            cout << sum << "\n";
        }
    }
    return 0;
}