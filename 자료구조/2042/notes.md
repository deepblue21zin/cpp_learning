# BOJ 1157 - 단어 공부

## Resource Budget (write first)
- N(데이터 개수) : 1 <= N <= 1,000,000
- M(변경 횟수) : 1 <= M <= 10,000
- K(합 구하는 횟수) : 1<= K <= 2,000,000
- ai​ (원소 값): −2^63∼2^63−1
Time: 2.0s -> O((M+K)log N)필요
RAM: 256MB -> 세그먼트 트리 배열 필요 (N x 4개)
Type risk: EXTREME 모든 수의 합과 개별 수가 long long 범위를 사용함. int 사용시 즉시 오답
Stack risk: YES 재귀 합수를 통한 트리 탐색 시 스택 깊이 고려 필요

## REQ
- 입력: 데이터 개수 N, 변경 횟수 M, 구간 합 횟수 K, 이후 N개의 초기 데이터와 M+K개의 쿼리
- 출력: b번째 수를 c로 바꾸기 (update), b부터 c까지의 합 출력하기 (sum)
- 제약: 데이터가 바뀌는 도중에 구간 합을 계속 구해야 하므로 Prefix Sum(누적합) 배열은 사용 불가(수정 시 O(N)소요)

## Approach
1) 데이터 구조 선택 : 수정과 조회를 모두 O(logN)에 처리하는 segment Tree또는 Fenwick Tree(BIT) 사용
2) 트리 초기화(init) : 리프 노드에 원본 값을 넣고, 부모 노드에 자식들의 합을 채우는 과정.
3) 업데이트(update) : 특정 노드 값이 바뀌면 해당 노드를 포함하는 모든 부모 노드들을 루트까지 올라가며 갱신.
4) 구간 합(query) : 주어진 범위 [b, c]에 속하는 노드들의 합을 재귀적으로 수집.

## Data structure
- Long Long Array : 11 tree[4000005]. N x 4크기의 전역 배열 선언
- Input Array : 11 a[1000005]. 초기 데이터 저장용

## Complexity
- Time Complexity : 틀리 생성 (O(N))
- Space Complexity : O(4N) (세그먼트 트리 노드 저장용 공간)

## Edge cases
- b > c: 합을 구하는 구간의 시작이 끝보다 클 경우 처리 (문제 조건상 b≤c가 보장되는지 확인).

- 수정 값의 범위: 변경되는 값이 음수일 수 있으며, 매우 큰 값일 수 있으므로 long long 연산 필수.

- 인덱스 오프셋: 문제의 인덱스(1-based)와 코드의 인덱스(0-based) 간의 차이 보정.

## Tests
- tests.txt 참고 (예제/경계/반례)

## Postmortem
- 데이터 타입 실수: int를 써서 합이 잘리는 경우 -> 전역 long long 선언으로 해결.

- 트리 크기 할당: 2N으로 잡았다가 런타임 에러(Out of Bounds) 발생 -> 4N으로 확장하여 해결.

- 비트 연산 활용: node*2 대신 node << 1을 사용하여 최적화 시도.