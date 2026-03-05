# BOJ 10866 - 덱

## Resource Budget (write first)
Constraints:
- 1 <= N <= 10,000 (명령 개수)
- push_front/push_back에 정수 1개가 주어짐

Symbols:
- N: 명령 수
- CAP: 덱 버퍼 크기 (보통 10,000 또는 10,005)
- head: front 원소 인덱스
- tail: 다음 push_back이 들어갈 인덱스(one-past-last)
- sz  : 현재 원소 개수

Time:
- Dominant loops:
  1) 명령 처리: N 번
  2) 각 명령은 O(1) (인덱스 갱신 + 배열 접근 1~2회)
- Big-O: O(N)
- worst-case ops ~= N * O(1)  (N=10,000이면 약 10,000회)

RAM:
- Major buffers only:
  - buf[CAP] int: CAP * 4 bytes
    - 예) CAP=10,000 -> 40,000 bytes (~39.1 KB)
  - head/tail/sz 및 임시 변수: 수십 bytes 수준(무시 가능)
- Total ~= 약 40 KB (+α)

Type risk:
- 인덱스/size: 0..CAP 범위 -> int32 안전
- 값 범위는 문제에서 보장(일반 int로 OK)
- (중요) back은 tail이 “다음 자리”라서 tail-1을 봐야 함

Stack risk:
- buf를 local로 두면 스택 부담 가능 -> struct 내부(자동)도 괜찮지만,
  임베디드 감각이면 static/global 또는 main 내 static 권장(재현성/예측성)

## REQ
- 입력: N, 이후 N줄에 명령
  - push_front X / push_back X
  - pop_front / pop_back
  - size / empty / front / back
- 출력:
  - pop_* / front / back: 비어있으면 -1, 아니면 값 출력
  - size: 원소 개수
  - empty: 비어있으면 1, 아니면 0

## Approach (4줄)
1) 정적 배열 buf[CAP] + head/tail/sz로 덱을 표현한다.
2) push_front: head를 한 칸 왼쪽으로 이동 후 저장, sz++.
3) push_back: tail 위치에 저장 후 tail을 한 칸 오른쪽으로 이동, sz++.
4) pop/front/back은 sz==0이면 -1, 아니면 head 또는 (tail-1) 위치를 이용해 O(1) 처리한다.

## Data structure
- 원형 버퍼(정적 배열):
  - 모든 연산을 O(1)로 만들고, 동적할당 없이 메모리 예측 가능
  - 인덱스 랩어라운드만 주의하면 안정적

## Complexity
- Time: O(N)
- Memory: O(CAP) (CAP=10,000이면 약 40KB)

## Edge cases (3개)
- empty 상태에서 pop/front/back 호출 -> 항상 -1
- push_front만 한 상태에서 back 호출 / push_back만 한 상태에서 front 호출 (한쪽만 넣었을 때도 정상)
- 랩어라운드(인덱스가 0에서 CAP-1로, CAP-1에서 0으로 넘어가는 상황)

## Tests
- tests.txt 참고 (예제/경계/반례)

## Postmortem
- (예) back에서 arr[tail]을 읽어서 오답 -> tail은 next slot, back은 (tail-1)
- (예) sz==0인데도 head/tail을 이동해 런타임 에러 -> empty면 즉시 return 규칙 고정