# BOJ 11723 - 집합

## Resource Budget (write first)
Constraints:
- 1 <= M <= 3,000,000 (명령 개수 매우 큼 → I/O 병목 가능)
- 1 <= x <= 20
Symbols:
- M: 명령 수
- x: 원소(1..20)
- S: 집합 상태(비트마스크)

Time:
- Dominant loops:
  1) 명령 처리: M 번 (각 명령은 O(1) 비트연산)
  2) 출력(check): 최대 M 번 (출력 버퍼링 여부가 전체 시간 좌우)
- Big-O: O(M)
- worst-case ops ~= M * (명령 디스패치 + 비트연산 몇 회)
  - 대략: 3,000,000 * O(1)  (실제로는 문자열 비교/입출력이 지배)

RAM:
- Major buffers only:
  - state: uint32_t S = 4 bytes
  - cmd token buffer: char cmd[8] ~= 8 bytes (또는 string 1개)
  - output buffer(권장): check 결과를 모을 버퍼
    - 최대 3,000,000줄, 각 줄 "0\n" 또는 "1\n" => 2 bytes/줄
    - worst output ~= 3,000,000 * 2 = 6,000,000 bytes (~5.7 MB)
    - (대안) 1MB 고정 버퍼 flush 방식이면 RAM ~= 1 MB로 제한 가능
- Total ~= 최소 수십 bytes ~ (출력 전략에 따라) 1MB 또는 ~6MB

Type risk:
- bit shift: (1u << (x-1))에서 x<=20 → uint32_t 안전
- M은 최대 3,000,000 → int32 안전
- 출력 줄 수/버퍼 크기(size_t) 사용 권장 (메모리 계산 시)
Stack risk:
- 큰 local 배열은 없음 → LOW
- 단, 출력 문자열을 통째로 누적하면 힙 사용량 커짐(최대 ~6MB) → 버퍼 flush 방식 권장

## REQ
- 입력: 첫 줄 M, 이후 M줄에 명령(add/remove/check/toggle/all/empty)
  - add/remove/check/toggle는 추가로 x가 주어짐
- 출력: check 명령마다 1(존재) 또는 0(없음) 출력
- 제약/주의:
  - M이 매우 커서 cin/cout, string 비교를 그대로 쓰면 TLE 위험 → 빠른 I/O/버퍼링 필요

## Approach (4줄)
1) 집합 S를 20비트 비트마스크(uint32_t)로 표현한다. (bit k가 1이면 k+1 원소 존재)
2) 각 명령을 읽고, add/remove/check/toggle/all/empty에 따라 비트연산으로 O(1) 처리한다.
3) check는 즉시 cout 하지 말고 출력 버퍼에 '0'/'1'과 '\n'를 쌓는다(또는 고정 버퍼 flush).
4) 모든 명령 처리 후 출력 버퍼를 한 번에 출력한다.

## Data structure
- uint32_t 비트마스크:
  - 원소 범위가 1..20으로 작고 고정 → 배열/셋보다 비트마스크가 가장 빠르고 메모리 예측 가능(4B)
- (출력) 버퍼(string 또는 char buffer):
  - check가 많을 때 출력 호출 횟수를 줄여 성능 확보

## Complexity
- Time: O(M) (명령당 O(1) 비트연산 + I/O)
- Memory: O(1) + output buffer
  - 출력 누적 시 worst ~6MB
  - 고정 버퍼 flush 시 ~1MB 수준으로 제한 가능

## Edge cases (3개)
- empty 후 check: 항상 0이어야 함
- all 후 check(1..20): 항상 1이어야 함
- 같은 원소에 add/remove 반복(중복 입력): 상태가 흔들리지 않아야 함(연산 무시 규칙)

## Tests (예제/경계/반례)
- tests.txt 참고
- 추천 자작 테스트:
  1) toggle/empty/all 섞기:
     M=8
     add 1
     add 1
     check 1 -> 1
     toggle 1
     check 1 -> 0
     all
     check 20 -> 1
     empty
     check 20 -> 0

## Postmortem
- 실수원인(예): check를 매번 cout로 바로 출력해서 TLE 발생
- 다음 방지 체크(예): check 출력은 버퍼에 누적 후 fwrite/flush로 처리(출력 호출 최소화)