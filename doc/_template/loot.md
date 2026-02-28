| 단계 | 내가 하는 행동(정확히)                                                      | 산출물/체크포인트                            |
| -: | ------------------------------------------------------------------ | ------------------------------------ |
|  0 | `boj/2563/` 폴더 생성                                                  | 폴더 생성 완료                             |
|  1 | 4개 파일 생성: `fast.cpp`, `clean.cpp`, `notes.md`, `tests.txt`         | 빈 파일 4개                              |
|  2 | **문제에서 제약만 뽑아 적기**: N≤100, 색종이는 10×10, 도화지 100×100, “도화지 밖으로 안 나감” | 제약 메모(입력은 도화지 밖으로 안 나감) ([Velog][1]) |
|  3 | `notes.md`를 열고 **Resource Budget부터** 채움(Time/RAM 숫자까지)             | notes Step0 완성                       |
|  4 | `tests.txt`에 **예제/경계/반례** 3개 넣기(기대 출력 포함)                          | tests 3케이스 저장                        |
|  5 | `fast.cpp`에 “격자 칠하고 카운트”로 최소 코드 작성                                 | fast.cpp 작성 완료                       |
|  6 | 컴파일(경고옵션 포함): `-O2 -Wall -Wextra -Wshadow -Wconversion`            | 경고 0 목표                              |
|  7 | tests 3개를 하나씩 붙여넣어 실행, 출력 확인                                       | 3/3 PASS                             |
|  8 | (선택) 백준 제출 → AC 확인                                                 | AC                                   |
|  9 | `clean.cpp`로 5분 리라이트(상수화/정적메모리/함수분리/경계안전)                          | clean.cpp 작성                         |
| 10 | clean.cpp도 tests 3개 다시 돌려 PASS 확인                                  | 3/3 PASS                             |
| 11 | `notes.md`에 Postmortem 1줄 작성(실수/방지 체크)                             | 회고 1줄                                |
| 12 | (선택) Git 커밋 2번: solve → refactor                                   | 증빙 끝                                 |

[1]: https://velog.io/%40ro_sie/%EB%B0%B1%EC%A4%80-JAVA-2563%EB%B2%88-%EC%83%89%EC%A2%85%EC%9D%B4?utm_source=chatgpt.com "백준 [JAVA] :: 2563번 색종이"

2. notes.md 를 작성
# BOJ 2563 - 색종이

## Resource Budget (write first)
Constraints:
- 1 <= N <= 100
- 도화지 100x100, 색종이 10x10
- 색종이가 도화지 밖으로 나가는 경우는 없음 (즉 x,y는 사실상 0..90 범위)  ※ 예제에 (90,90)도 존재 :contentReference[oaicite:1]{index=1}

Symbols:
- N = 색종이 개수 (<=100)
- B = 100 (board size)
- P = 10  (paper size)

Time:
- Dominant loops:
  1) 칠하기: N * P * P = N * 100
  2) 카운트: B * B = 10,000
- Big-O: O(N*P^2 + B^2) (여기선 B,P가 상수라 사실상 O(N)+O(1))
- worst-case ops ~= 100*100 + 10,000 = 20,000 cell ops (N=100일 때)

RAM:
- Major buffers:
  - grid[100][100] uint8_t: 10,000 * 1B = 10,000 bytes (~9.8KB)
- Total ~= ~10KB + vars (무시 가능)
Type risk:
- area max = 10,000 -> int32 OK
Stack risk:
- grid를 local로 두면 스택 위험 가능 -> static/global 권장

## REQ
- 입력: N, 이후 N줄 (x,y) 좌표
- 출력: 검은 영역 넓이(겹침은 1번만 계산)

## Approach (4줄)
1) 100x100 grid를 0으로 초기화
2) 각 색종이 (x,y)에 대해 [x..x+9][y..y+9]를 1로 칠함
3) grid 전체에서 1의 개수를 셈
4) 개수를 출력

## Edge cases
- 완전 겹침(같은 좌표 여러 번)
- 부분 겹침(예: (0,0) + (5,5))
- 경계(예: (90,90))

## Tests
- tests.txt 참고

## Postmortem
- (예) r<x+10, c<y+10 범위를 잘못 잡아 OOB 위험 -> 상수(P=10) + 상한 min(,100) 규칙 고정

3. test.txt를 작성
# T1: 공식 예제 (출력 260)
3
3 7
15 7
5 2
# expected:
260

# T2: 최소/기본 경계 (한 장, (0,0))
1
0 0
# expected:
100

# T3: 부분 겹침 반례 (25칸 겹침)
2
0 0
5 5
# expected:
175

4. fast.cpp를 먼저 만들고 AC찍기
// fast.cpp - BOJ 2563
// Step0:
// CONSTS: B=100, P=10
// TYPE: area<=10000 -> int OK, grid=uint8_t
// MEM: grid[100][100]=10,000B -> static으로 스택 회피

#include <iostream>
#include <cstdint>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int B = 100;
    constexpr int P = 10;

    static uint8_t grid[B][B] = {0};

    int N;
    cin >> N;

    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        for (int r = x; r < x + P; ++r) {
            for (int c = y; c < y + P; ++c) {
                grid[r][c] = 1U;
            }
        }
    }

    int area = 0;
    for (int r = 0; r < B; ++r) {
        for (int c = 0; c < B; ++c) {
            area += (grid[r][c] != 0U) ? 1 : 0;
        }
    }

    cout << area << '\n';
    return 0;
}
테스트:

./fast 실행 → tests.txt의 T1 블록만 붙여넣기 → 260 확인

T2 붙여넣기 → 100 확인

T3 붙여넣기 → 175 확인

5. clean.cpp로 5분 리라이트
constexpr 상수화

static 정적 메모리

함수 2개 분리

경계 안전(입력은 안전하다고 해도 습관)

주석에 Time/RAM 명시