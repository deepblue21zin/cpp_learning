# BOJ 1157 - 단어 공부

## Resource Budget (write first)
- n <= 100,000
- ai <= 1,000,000
- x <= 2,000,000
Time: O(N log N) (sort) + O(N) (two pointers)
RAM: a[N] int (4*N bytes). N=100,000 => ~400KB
Type risk: NO (sum <= 2,000,000 fits in int32), count <= N fits in int32
Stack risk: YES if a[N] is local -> static/global or heap(vector) 권장

## REQ
- 입력: n, 수열 a[0..n-1], 목표합 x
- 출력: i<j 이면서 a[i]+a[j]=x인 쌍의 개수
- 제약: n이 커서 O(N^2) 금지

## Approach
1) 수열을 정렬한다.
2) 양끝 포인터 i=0, j=n-1에서 시작한다.
3) 합이 x보다 작으면 i++, 크면 j--, 같으면 count++ 후 i++, j--.
4) i<j 동안 반복한다.

## Data structure
- 배열/벡터: 입력을 저장하기 위한 선형 컨테이너
- 정렬 후 투포인터는 추가 메모리 거의 없이 동작

## Complexity
- Time: O(N log N)
- RAM: a[N]*4 bytes (N=100,000이면 ~400KB)

## Edge cases
- n<2면 항상 0
- 중복 값 다수(예: 1 1 1 1, x=2)
- 쌍이 아예 없는 경우

## Tests
- tests.txt 참고 (예제/경계/반례)

## Postmortem
- (예) ==x일 때 포인터 이동을 한쪽만 해서 무한루프/중복카운트 발생 -> 규칙(i++, j--) 고정