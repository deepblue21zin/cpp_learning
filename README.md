# BOJ → Embedded/ADAS Portfolio 루틴 (fast/clean/tests/notes 표준)

백준 풀이를 “그냥 AC”로 끝내지 않고, **품질 증빙(자원예산/테스트/문서/리팩터)**까지 남겨서 포트폴리오로 쌓는 루틴이다.  
목표는 문제 수가 늘어날수록 폴더 자체가 “면접에서 보여줄 수 있는 결과물”이 되게 만드는 것.

---

## 1) 폴더/증빙 구조 (모든 문제 공통)

각 문제 폴더는 아래 4개 파일을 **항상** 가진다.


boj/<problem_id>/
fast.cpp # 대회/실전용: 빠르게 AC
clean.cpp # 포트폴리오용: 가독/안전/정적할당/명확한 설계 흔적
tests.txt # 내가 만든 테스트 입력 모음(예제+경계+반례)
notes.md # 요구사항/설계/복잡도/자원예산/엣지/회고(면접 스크립트)


**이 구조 자체가 품질 증거**다.

---

## 2) 문제 1개 처리 루틴 (고정 순서)

### Step 0) (가장 먼저) notes.md에 Resource Budget 1줄
코드 작성 전에, 문제 읽자마자 `notes.md` 상단에 아래를 작성한다.

- **Time:** O(?) (최악 입력 기준)
- **RAM:** 주요 배열/버퍼 바이트 계산(대략이라도 숫자)
- **Type risk:** 오버플로 가능성 YES/NO + 이유 1문장
- **Stack risk:** 큰 배열 로컬이면 위험 → static/global 권장

> 포인트: “스택/메모리 감각”이 임베디드 역량으로 바로 보인다.

---

### Step 1) fast.cpp로 AC (속도 우선, 규칙 3개만 지키기)
AC를 최우선으로 찍되, 아래 3가지는 무조건 지킨다.

- **(A) 큰 버퍼 로컬 금지:** `static` 또는 전역으로 (스택 보호)
- **(B) 자료형은 최악값 기준:** 최대치 1줄 계산 후 결정
- **(C) 디버그 출력은 게이트:** 제출 시 한 줄로 꺼지게

예시(컨셉):
```cpp
#ifdef DEBUG
  #define DBG(...) do { fprintf(stderr, __VA_ARGS__); } while(0)
#else
  #define DBG(...) do {} while(0)
#endif

또는:

constexpr bool kDebug = false;
if (kDebug) { /* debug prints */ }
Step 2) tests.txt에 “3종 세트” 누적 (최소 4개)

각 문제 끝나면 tests.txt에 아래를 최소로 남긴다.

예제 1개 (문제 제공)

경계 1개 (최소/최대)

반례 2개 (내가 만든 것)

권장 포맷:

# Case 1: example
<input>
# expect: <output>

# Case 2: boundary
<input>
# expect: <output>

# Case 3: counterexample
<input>
# expect: <output>

# Case 4: counterexample
<input>
# expect: <output>

포인트: “반례를 만드는 습관”이 실력이다.

Step 3) clean.cpp로 5분 리팩터 (포트폴리오화)

AC 후 딱 5분만 써서 clean.cpp를 만든다. 순서 고정:

디버그 출력 제거/게이트 정리

로직을 2~3개 함수로 분리

정적 크기 컨테이너 우선 (std::array, 고정 배열)

입력 검증/범위 명시(가능한 범위에서)

주석 2줄만 추가

“왜 이 방식”

“복잡도/메모리”

추천 함수 분리 예:

parse_input()

solve()

post_process() 또는 count_*() / find_*()

Step 4) notes.md 마감 (면접 답변 스크립트로 완성)

notes.md는 아래 템플릿을 고정으로 사용하고, 내용은 문제별로 채운다.

3) notes.md 템플릿 (복붙용)
# BOJ <problem_id> - <title>

## Resource Budget (write first)
Time: O(?) (worst-case)
RAM: (bytes) 주요 배열/버퍼 계산
Type risk: YES/NO (근거 1문장)
Stack risk: YES/NO (큰 로컬 배열이면 static/global)

## REQ
- 입력:
- 출력:
- 제약 핵심(3줄 내):

## Approach
1)
2)
3)
4)
5) (한글로 5줄 이내)

## Data structure
- 선택한 자료구조:
- 선택 이유(배열 vs map/정렬 vs 해시 등, 2줄)

## Complexity
- Time: O(?)
- RAM: ~ ? bytes

## Edge cases
- 1)
- 2)
- 3)

## Tests
- tests.txt 참고 (예제/경계/반례)

## Postmortem (1줄)
- 오늘 실수 원인 + 방지 체크(다음부터 지킬 규칙 1개)
4) 검증/측정 방법 (문제마다 고정으로 남길 것)
성능 지표 (notes.md에 고정)

Time: O(?)

RAM: bytes (대략이라도 숫자)

Type risk: 최악값 근거

Stack risk: 로컬 배열 위험 여부

테스트 플랜 (최소 기준)

예제 1 + 경계 1 + 반례 2 = 최소 4개

디버깅 포인트 (DEBUG에서만)

중간 값 출력은 “고정 포맷”으로: 인덱스/값/누적값

인덱스 방어(디버그에서만):

assert(0 <= idx && idx < K) 류

5) Git 기록 규칙 (증빙 강화)

문제 1개당 커밋 2개로 나누면 “내가 한 일”이 분리되어 보인다.

boj/<id>: AC (fast)

boj/<id>: clean + tests + notes