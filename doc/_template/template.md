<notes.md>
Time 계산법 (4단계 레시피)
1) “변수(제약)”를 기호로 바꿔 적기

예:

N = 색종이 개수 (최대 100)

B = 보드 한 변 크기 (100)

P = 색종이 한 변 크기 (10)

2) 코드에서 “큰 루프”만 뽑기

색종이 칠하기: for i in N 안에 10×10 루프

전체 면적 카운트: 100×100 루프

3) 반복 횟수를 곱으로 적기 (이게 ops 추정치)

칠하기 연산 수 ≈ N * P * P

카운트 연산 수 ≈ B * B

총 연산 수 ≈ N*P^2 + B^2

4) Big-O와 “최악 숫자”를 같이 적기

Big-O: O(N*P^2 + B^2)

최악 ops: N=100, P=10, B=100이면

N*P^2 = 100*100 = 10,000

B^2 = 10,000

합 ≈ 20,000 cell ops
→ 결론: 이 문제는 사실상 **상수 시간(보드가 고정)**이지만, notes에는 위처럼 쓰면 “근거 있는 시간 추정”이 된다.

RAM 계산법 (3단계 레시피)
1) “큰 메모리”만 리스트업

대부분은 배열/벡터/버퍼가 전부다. (나머지 int 몇 개는 무시해도 됨)

2) 각 항목을 원소 개수 × 자료형 바이트로 계산

BOJ/C++에서 보통 이렇게 가정(로컬에서 sizeof로 확인 가능):

타입	보통 바이트(가정)
uint8_t / char	1
int	4
long long	8
bool	보통 1(구현/패딩 영향 가능)
3) “Stack risk”까지 같이 판단

local 배열이면 스택 사용 → 크면 위험

static/global이면 데이터 영역 → 예측 가능(임베디드 스타일)

BOJ 2563에 맞춘 notes.md Time/RAM “정답 스타일” 예시
Time (2563)

칠하기: N * 10 * 10

카운트: 100 * 100

최악(N=100): 10,000 + 10,000 = 20,000 cell ops

notes.md에 쓰는 형태:

Time: O(N*10*10 + 100*100) ≈ max 20,000 cell ops

RAM (2563)

너 코드가 int paper[101][101] 라고 했지? 그럼:

원소 개수: 101*101 = 10,201

int 4바이트 가정 → 10,201 * 4 = 40,804 bytes ≈ 39.9 KB

임베디드/ADAS 스타일로 uint8_t grid[100][100]로 줄이면:

100*100 = 10,000

uint8_t 1바이트 → 10,000 bytes ≈ 9.8 KB

즉 notes.md에는 이렇게 쓰면 깔끔해:

RAM: grid[100][100] uint8_t = 10,000B (~9.8KB) + vars (<100B)

Stack risk: YES if local array -> static/global 권장

네가 붙여넣기 좋은 “Resource Budget 템플릿”
## Resource Budget (write first)
- Constraints: N<=..., ...
- Symbols: N=..., B=..., etc.

Time:
- Dominant loops: (1) ..., (2) ...
- O(...), worst-case ops ≈ ...

RAM:
- Major buffers:
  - buf1: count * sizeof(type) = ... bytes
  - buf2: ...
- Total ≈ ... KB
Type risk:
- max value 계산: ... -> int32 OK/NO
Stack risk:
- local big array? YES/NO -> static/global 권장
리스크 & 실패모드 (이렇게 하면 망한다)

Big-O만 쓰고 숫자(ops/bytes) 안 쓰기: 감으로 때우게 되고 실버부터 TLE/WA 원인분석이 느려짐.

int로 배열 잡는 습관: “그냥 되겠지” 하다가 스택/메모리 습관이 망가짐(임베디드 면접에서 약점).

오버플로 최악값 계산 생략: 합/곱 문제에서 WA 반복.

검증 및 측정 방법

로컬에서 sizeof(int), sizeof(long long) 찍어서 “내 가정(4,8)” 확인

2563은 디버그로 칠한 셀 개수 상한(<=10000) 체크: area <= 10000 어기면 로직/인덱스 문제

Time은 실제로는 빠르지만, notes에 최악 ops를 적는 게 목적(근거 문서화)

<코딩 루틴 체화>
1. 코딩 시작 전 90초 : Step0 3줄
- CONSTS : 고정값/범위
- TYPE RISK : 최악값 계산으로 int/ll 결정
- MEM : 큰 버퍼(배열/벡터) 크기와 위치(local 금지 여부)
ex)
// Step0:
// CONSTS: board=100, paper=10
// TYPE: area<=10000 -> int OK, grid=uint8_t(1B)
// MEM: grid[100][100]=10000B, local 금지 -> static/global
2. fast -> clean 2단계 루틴
- fast.cpp(AC 목적)
-- 문제 풀이는 여기서 끝내도 됨(하지만 최소 조건 있음)
-- 최소 조건 3개
--- 매직넘버 상수화(최소2개)
--- 오버플로우 방지(1LL, int64_t등)
--- 루프/인덱스 범위 한 번 확인
- clean.cpp(임베디드 스타일, 선택 적용)
-- 매 문제 다 하지 말고 : 하루 2문제 중 1개만 clean처럼 비율 고정
-- clean에서만 챙길 것
--- constexpr상수
--- 정적할당 우선(가능하면 static/std::array)
--- 함수 2개로 분리(입력/처리 or 처리/출력)
--- 경계/OOB 안전(문제 제약을 믿더라도 습관화)
--- 주석 2줄 : 왜 이 방식 + Time/RAM

clean.cpp template
// clean.cpp - BOJ XXXXX
// Step0:
// CONSTS:
// TYPE:
// MEM:

#include <iostream>
#include <cstdint>
#include <algorithm>

namespace {
    // 1) constexpr 상수
    // constexpr int kSomething = ...;

    // 2) 정적 버퍼(필요할 때만)
    // static std::uint8_t buf[...];

#ifdef DEBUG
    #define DLOG(x) do { std::cerr << x << '\n'; } while (0)
#else
    #define DLOG(x) do {} while (0)
#endif

    // 3) helper 함수(최대 2~3개)
    // static void solve(...);
    // static int calc(...);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 4) 입력
    // 5) 처리
    // 6) 출력
    return 0;
}

A. 항상 할 것(가성비 최고, 실수 방지)

A1. 기본 I/O세팅
ios::sync_with_stdio(false);
cin.tie(nullptr);

A2. 타입 고정
인덱스/카운트: int(BOJ 대부분 OK) / 크면 int64_t

비트/마스크/플래그: uint32_t/uint64_t

signed/unsigned 섞지 말기(버그의 근원)

A3. 상수는 매직넘버 금지
- 한 파일 기준으로는 아래가 충분
constexpr int ALPHA = 26;
constexpr int MAX_N = 200000;
- const int도 되지만, 습관은 constexpr가 더 좋음

A4. 네임스페이스 정리
- 백준에서는 과한 설계 필요 없고, 정리용으로만
namespace {
  constexpr int ALPHA = 26;
}
- 전염 오염 줄이고, 상수/헬퍼를 묶는 용도

A5. 함수 2개 분리(현업형)
- read_input() / solve()정도만 분리해도 급상승

B. 문제에 따라 할 것(ROI좋을 때만)

B1. FastScanner(fread) /출력 버퍼링
- M이 수백만줄이거나 cin/cout로 TLE경험하면 도입
예: 11723은 M=3,000,000이라 “도입 가치 있음”.

B2. std::array, vector.reserve()
- 고정크기면 std::array<int, 26> 가 좋고
- 동적이면 reserve로 재할당 줄이기

B3. assert/디버그 로그 (로컬에서만)
- 제출전 #ifdef DEBUG로 켜고, 정답 나오면 제거

#include <bits/stdc++.h>
using namespace std;

namespace {
  constexpr int ALPHA = 26;
}

static void solve() {
  // TODO
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  solve();
  return 0;
}