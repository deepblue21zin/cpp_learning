# C++ 포인터와 임베디드/ADAS 프로그래밍 가이드

> 백준 1157번 문제 분석을 통한 포인터 개념 이해 및 임베디드/ADAS 실무 코딩 기법

---

## 📑 목차

1. [백준 1157번 문제 분석](#백준-1157번-문제-분석)
2. [Algorithm 라이브러리 함수](#algorithm-라이브러리-함수)
3. [포인터 완전 정복](#포인터-완전-정복)
4. [임베디드/ADAS 필수 지식](#임베디드adas-필수-지식)
5. [메모리 최적화 기법](#메모리-최적화-기법)
6. [실무 코딩 패턴](#실무-코딩-패턴)

---

# 백준 1157번 문제 분석

## 문제 설명
- 알파벳 대소문자로 된 단어에서 가장 많이 사용된 알파벳 찾기
- 가장 많이 사용된 알파벳이 여러 개면 `?` 출력

## 원본 코드

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string word;
    cin >> word;
    int maxCount = 0;
    
    int alphabet[26] = {0,};
    
    for(char c : word) {
        if(isupper(c)) {
            alphabet[c - 'A']++;
        } else {
            alphabet[c - 'a']++;
        }
    }
    
    int maxIndex = distance(alphabet, max_element(alphabet, alphabet + 26));
    maxCount = alphabet[maxIndex];
    int cntMax = 0;
    
    for (int i=0; i < 26; i++) {
        if(alphabet[i] == maxCount) {
            cntMax++;
        }
    }
    
    if(cntMax > 1) {
        cout << '?';
    } else {
        cout << (char)(maxIndex + 'A');
    }
    
    return 0;
}
```

## 1차 코드의 문제점

### 잘못된 코드
```cpp
for(int i = 0; i<26; i++){
    if(alphabet[i] == maxCount && i != maxIndex){
        cout << '?';
    } else if(alphabet[i] == maxCount){
        cout << (char)(i + 'A'); 
    }
}
```

### 문제 분석: "aabb" 입력 시

| i | alphabet[i] | 조건 | 출력 |
|---|-------------|------|------|
| 0 | 2 | `i == maxIndex` | **'A'** |
| 1 | 2 | `alphabet[1] == maxCount && i != maxIndex` | **'?'** |

**결과**: `A?` 출력 (잘못됨!)

### 문제점
1. 루프를 돌면서 조건을 만족할 때마다 **즉시 출력**
2. 최댓값이 여러 개인지 **미리 확인하지 않음**
3. 여러 번 출력될 수 있음

## 수정된 코드 (정답)

```cpp
int cntMax = 0;

// 1단계: 최댓값 개수 먼저 확인
for (int i=0; i < 26; i++) {
    if(alphabet[i] == maxCount) {
        cntMax++;
    }
}

// 2단계: 개수에 따라 출력
if(cntMax > 1) {
    cout << '?';
} else {
    cout << (char)(maxIndex + 'A'); 
}
```

### 개선점
1. **출력 전에 먼저 개수를 확인**
2. **한 번만 출력** (중복 출력 방지)
3. 로직이 명확하고 간결함

---

# Algorithm 라이브러리 함수

## 1. fill(시작, 끝, 값)

```cpp
fill(alphabet, alphabet + 26, 0);
```

- **기능**: 배열의 특정 범위를 같은 값으로 채움
- **파라미터**: 
  - `alphabet`: 시작 포인터
  - `alphabet + 26`: 끝 포인터 (끝은 포함 안 됨)
  - `0`: 채울 값

### 예시
```cpp
int arr[5];
fill(arr, arr + 5, 10);
// arr = {10, 10, 10, 10, 10}
```

## 2. max_element(시작, 끝)

```cpp
max_element(alphabet, alphabet + 26)
```

- **기능**: 범위 내에서 **최댓값을 가진 원소의 포인터** 반환
- **반환값**: 포인터 (주소값)

### 예시
```cpp
int arr[5] = {3, 7, 2, 9, 1};
int* maxPtr = max_element(arr, arr + 5);
// maxPtr은 arr[3]의 주소를 가리킴 (값 9)
cout << *maxPtr; // 9 출력
```

### ⚠️ 중요
- `max_element`는 **최댓값이 여러 개 있어도 첫 번째 것만** 반환

## 3. distance(시작, 끝)

```cpp
distance(alphabet, max_element(alphabet, alphabet + 26))
```

- **기능**: 두 포인터 사이의 거리(인덱스 차이) 계산
- **반환값**: 정수 (인덱스)

### 예시
```cpp
int arr[5] = {3, 7, 2, 9, 1};
int index = distance(arr, max_element(arr, arr + 5));
// index = 3 (arr[3]에 최댓값 9가 있음)
```

### 동작 과정 ("aabb" 입력 시)
```
alphabet = {2, 2, 0, 0, ..., 0}

1. max_element(alphabet, alphabet + 26) 
   → alphabet[0]의 주소 반환 (값 2인 첫 번째 원소)

2. distance(alphabet, alphabet의 주소)
   → 0 반환 (첫 번째 위치)

3. maxIndex = 0
4. maxCount = alphabet[0] = 2
```

---

# 포인터 완전 정복

## 포인터란?

**포인터 = 메모리 주소를 저장하는 변수**

```cpp
int x = 10;      // 일반 변수: 값을 저장
int* ptr = &x;   // 포인터: 주소를 저장
```

### 메모리 구조

```
변수 x:
┌──────────┬──────────┬──────┐
│   이름   │   주소   │  값  │
├──────────┼──────────┼──────┤
│    x     │   1000   │  10  │
└──────────┴──────────┴──────┘

포인터 ptr:
┌──────────┬──────────┬──────┐
│   이름   │   주소   │  값  │
├──────────┼──────────┼──────┤
│   ptr    │   2000   │ 1000 │ ← x의 주소 저장
└──────────┴──────────┴──────┘
```

## 핵심 연산자

### & (주소 연산자)
```cpp
int x = 10;
int* ptr = &x;  // x의 주소를 ptr에 저장

cout << &x;     // 1000 (x의 주소)
cout << ptr;    // 1000 (같은 주소)
```

### * (역참조 연산자)
```cpp
int x = 10;
int* ptr = &x;

cout << *ptr;   // 10 (ptr이 가리키는 곳의 값)
*ptr = 20;      // ptr이 가리키는 곳의 값 변경
cout << x;      // 20 (x가 변경됨)
```

## 배열과 포인터

**배열 이름 = 첫 번째 원소의 주소**

```cpp
int arr[5] = {10, 20, 30, 40, 50};
//           [0] [1] [2] [3] [4]
// 주소:    1000 1004 1008 1012 1016

cout << arr;        // 1000 (배열 시작 주소)
cout << &arr[0];    // 1000 (같은 의미)
cout << arr + 1;    // 1004 (다음 원소 주소)
cout << arr + 2;    // 1008 (그 다음 원소 주소)
```

### 포인터 산술 연산

```cpp
int arr[5] = {10, 20, 30, 40, 50};
int* ptr = arr;     // ptr = 1000

ptr + 0  →  1000   (arr[0]의 주소)
ptr + 1  →  1004   (arr[1]의 주소)  // +4 바이트 (int 크기)
ptr + 2  →  1008   (arr[2]의 주소)  // +8 바이트
ptr + 3  →  1012   (arr[3]의 주소)  // +12 바이트
```

**중요**: `ptr + n`은 `n * sizeof(자료형)` 바이트만큼 이동!

## 타입별 결과 정리

| 연산 | 결과 타입 | 의미 | 예시 |
|------|-----------|------|------|
| `포인터 - 포인터` | **인덱스 (int)** | 두 위치 사이의 원소 개수 | `(arr+3) - arr = 3` |
| `*포인터` | **값** | 포인터가 가리키는 곳의 값 | `*arr = 10` |
| `포인터[n]` | **값** | n번째 원소의 값 | `arr[2] = 30` |
| `포인터 + n` | **포인터 (주소)** | n번째 원소의 주소 | `arr + 2 = 1008` |
| `&변수` | **포인터 (주소)** | 변수의 주소 | `&arr[2] = 1008` |

## 인덱스로 저장되는 경우

### 1. 포인터 - 포인터
```cpp
int arr[5] = {10, 20, 30, 40, 50};

int index = (arr + 3) - arr;
//          ↑         ↑
//        1012      1000
//        (1012 - 1000) / 4 = 3

cout << index;  // 3 (인덱스)
```

### 내부 계산 과정
```cpp
ptr - arr
= 1012 - 1000        // 바이트 차이
= 12                 // 12바이트 차이
= 12 / sizeof(int)   // int 크기(4바이트)로 나눔
= 12 / 4
= 3                  // 인덱스!
```

### 2. distance 함수
```cpp
int arr[5] = {10, 20, 30, 40, 50};

int index = distance(arr, arr + 3);
//                   ↑      ↑
//                 1000   1012
//          내부적으로 포인터 뺄셈 수행

cout << index;  // 3 (인덱스)
```

## 값으로 저장되는 경우

### 1. 역참조 연산자 *
```cpp
int arr[5] = {10, 20, 30, 40, 50};

int value = *arr;        // arr[0]의 값
cout << value;           // 10

int value2 = *(arr + 3); // arr[3]의 값
cout << value2;          // 40
```

### 2. 배열 인덱스 []
```cpp
int arr[5] = {10, 20, 30, 40, 50};

int value = arr[3];
cout << value;  // 40 (값)
```

## 주소(포인터)로 저장되는 경우

### 1. 주소 연산자 &
```cpp
int arr[5] = {10, 20, 30, 40, 50};

int* ptr = &arr[2];  // arr[2]의 주소
cout << ptr;         // 1008 (주소)
```

### 2. max_element
```cpp
int arr[5] = {10, 20, 30, 40, 50};

int* maxPtr = max_element(arr, arr + 5);
cout << maxPtr;  // 1016 (arr[4]의 주소)
```

## 배열의 연속성과 인덱스

### 배열의 특성
```
메모리:
┌──────┬──────┬──────┬──────┬──────┐
│  10  │  20  │  30  │  40  │  50  │
└──────┴──────┴──────┴──────┴──────┘
  ↑      ↑      ↑      ↑      ↑
 1000   1004   1008   1012   1016  (주소)
  [0]    [1]    [2]    [3]    [4]   (인덱스)
```

**배열은 연속된 메모리 구조** → 포인터 뺄셈 = 자동으로 인덱스 계산

```cpp
(1012 - 1000) / 4 = 3
→ 시작점부터 3칸 떨어져 있음
→ 인덱스 3!
```

## 종합 실습 예제

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int arr[5] = {10, 20, 50, 30, 40};
    
    // ========== 주소(포인터) ==========
    int* ptr1 = arr;                              // 1000
    int* ptr2 = arr + 2;                          // 1008
    int* maxPtr = max_element(arr, arr + 5);      // 1008
    
    cout << "주소들:\n";
    cout << "arr: " << arr << endl;               // 1000
    cout << "ptr1: " << ptr1 << endl;             // 1000
    cout << "ptr2: " << ptr2 << endl;             // 1008
    cout << "maxPtr: " << maxPtr << endl;         // 1008
    
    // ========== 인덱스 ==========
    int idx1 = ptr2 - arr;                        // 2
    int idx2 = distance(arr, maxPtr);             // 2
    int idx3 = maxPtr - arr;                      // 2
    
    cout << "\n인덱스들:\n";
    cout << "idx1: " << idx1 << endl;             // 2
    cout << "idx2: " << idx2 << endl;             // 2
    cout << "idx3: " << idx3 << endl;             // 2
    
    // ========== 값 ==========
    int val1 = *ptr2;                             // 50
    int val2 = *maxPtr;                           // 50
    int val3 = arr[2];                            // 50
    int val4 = *(arr + 2);                        // 50
    
    cout << "\n값들:\n";
    cout << "val1: " << val1 << endl;             // 50
    cout << "val2: " << val2 << endl;             // 50
    cout << "val3: " << val3 << endl;             // 50
    cout << "val4: " << val4 << endl;             // 50
    
    return 0;
}
```

## 핵심 암기 공식

```cpp
// 인덱스를 얻고 싶을 때
인덱스 = 포인터 - 배열시작주소
인덱스 = distance(시작, 포인터)

// 값을 얻고 싶을 때
값 = *포인터
값 = 배열[인덱스]

// 주소를 얻고 싶을 때
주소 = &변수
주소 = 배열 + 인덱스
주소 = max_element(...)
```

---

# 임베디드/ADAS 필수 지식

## 1. 메모리 관리 핵심 개념

### ⚠️ 피해야 할 것들

```cpp
// ❌ 피해야 할 것
string word;              // 힙 메모리 동적 할당 (예측 불가능)
vector<int> data;         // 힙 메모리 (ADAS에서 위험)
new / delete             // 동적 메모리 할당 (금지!)
```

### ✅ 권장하는 것들

```cpp
// ✅ 권장
char word[100];          // 스택 메모리 (고정 크기)
int alphabet[26];        // 정적 배열
const int MAX_SIZE = 26; // 컴파일 타임 상수
```

## 2. 임베디드/ADAS 필수 라이브러리 & 함수

### 사용 가능한 STL (제한적)

```cpp
// ✅ 가능 (정적 크기)
#include <array>
std::array<int, 26> alphabet;  // 스택에 할당

// ⚠️ 조건부 가능
#include <algorithm>     // sort, min, max 등
// 단, 동적 메모리 안 쓰는 함수만

// ❌ 회피
#include <vector>        // 동적 할당
#include <string>        // 동적 할당
#include <map>          // 동적 할당
```

### 필수 함수들

#### 메모리 조작
```cpp
#include <cstring>
memset(buffer, 0, size);      // 메모리 초기화
memcpy(dest, src, size);      // 메모리 복사
memmove(dest, src, size);     // 겹치는 메모리 복사
memcmp(buf1, buf2, size);     // 메모리 비교
```

#### 비트 연산 (레지스터 제어)
```cpp
#include <cstdint>
uint32_t reg = 0x00;
reg |= (1 << 5);              // 비트 SET
reg &= ~(1 << 5);             // 비트 CLEAR
reg ^= (1 << 5);              // 비트 TOGGLE
bool bit = (reg >> 5) & 1;    // 비트 READ
```

#### 수학 함수
```cpp
#include <cmath>
abs(), fabs()                 // 절댓값
sqrt()                        // 제곱근
sin(), cos()                  // 삼각함수 (ADAS 좌표 변환)
atan2()                       // 각도 계산
```

## 3. ADAS 특화 필수 지식

### 실시간 제약 (Real-time Constraints)

```cpp
// ❌ 나쁜 예 - 시간 복잡도 불확실
for(int i = 0; i < n; i++) {
    if(condition) {
        // 가변 시간 로직
    }
}

// ✅ 좋은 예 - 예측 가능한 시간
for(int i = 0; i < FIXED_SIZE; i++) {
    // 고정 시간 로직
}
```

### 안전성 (Safety-critical)

```cpp
// ❌ 버퍼 오버플로우 위험
char buffer[10];
cin >> buffer;  // 위험!

// ✅ 안전한 입력
char buffer[10];
cin.width(10);
cin >> buffer;

// 또는
fgets(buffer, sizeof(buffer), stdin);
```

### MISRA C++ 규칙 (자동차 업계 표준)

```cpp
// ✅ const 사용
const int MAX_OBJECTS = 100;

// ✅ 명시적 타입 변환
int x = static_cast<int>(3.14);

// ✅ NULL 대신 nullptr (C++11)
int* ptr = nullptr;

// ✅ 초기화 명확히
int count = 0;  // 반드시 초기화
```

---

# 메모리 최적화 기법

## 현재 코드 메모리 분석

```cpp
string word;              // 힙 메모리 (크기 가변)
int maxCount = 0;         // 스택 4바이트
int alphabet[26] = {0,};  // 스택 104바이트 (26*4)
int maxIndex;             // 스택 4바이트
int cntMax = 0;           // 스택 4바이트
```

**총 스택**: ~116바이트  
**힙**: 가변 (string 길이에 따라)

## 최적화 버전 1: 기본 최적화

```cpp
#include <cstdio>    // scanf, printf (C 스타일, 더 가벼움)
#include <cctype>    // toupper
#include <cstring>   // memset

int main() {
    char word[1000001];  // 최대 입력 크기
    scanf("%s", word);   // cin보다 빠름
    
    int alphabet[26];
    memset(alphabet, 0, sizeof(alphabet));  // fill보다 빠름
    
    // 대소문자 카운팅
    for(int i = 0; word[i] != '\0'; i++) {
        char c = toupper(word[i]);
        alphabet[c - 'A']++;
    }
    
    // 최댓값 찾기 (algorithm 없이)
    int maxCount = 0;
    int maxIndex = 0;
    for(int i = 0; i < 26; i++) {
        if(alphabet[i] > maxCount) {
            maxCount = alphabet[i];
            maxIndex = i;
        }
    }
    
    // 최댓값 개수 세기
    int cntMax = 0;
    for(int i = 0; i < 26; i++) {
        if(alphabet[i] == maxCount) {
            cntMax++;
        }
    }
    
    // 출력
    if(cntMax > 1) {
        printf("?\n");
    } else {
        printf("%c\n", 'A' + maxIndex);
    }
    
    return 0;
}
```

**개선점**:
- `string` → `char[]`: 힙 메모리 제거
- `cin/cout` → `scanf/printf`: 더 빠르고 가벼움
- `fill` → `memset`: 더 빠른 초기화
- `max_element` 제거: 단순 루프로 대체

## 최적화 버전 2: 최대 최적화 (ADAS 스타일)

```cpp
#include <cstdio>
#include <cstring>

#define MAX_LEN 1000001
#define ALPHABET_SIZE 26

int main() {
    static char word[MAX_LEN];  // BSS 섹션
    scanf("%s", word);
    
    int alphabet[ALPHABET_SIZE] = {0};
    
    // 비트 연산으로 대소문자 통합 카운팅
    for(const char* p = word; *p; p++) {
        int idx = (*p & 0x5F) - 'A';  // 대문자로 변환
        alphabet[idx]++;
    }
    
    // 원패스로 최댓값과 개수 동시 계산
    int maxCount = 0, maxIdx = 0, cntMax = 0;
    
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(alphabet[i] > maxCount) {
            maxCount = alphabet[i];
            maxIdx = i;
            cntMax = 1;
        } else if(alphabet[i] == maxCount) {
            cntMax++;
        }
    }
    
    printf("%c\n", (cntMax > 1) ? '?' : 'A' + maxIdx);
    
    return 0;
}
```

**추가 최적화**:
- **비트 연산으로 대소문자 변환**: 함수 호출 제거
- **원패스 알고리즘**: 루프 2번 → 1번
- **static 키워드**: 큰 배열은 BSS 영역에 배치
- **포인터 활용**: 배열 인덱스보다 빠를 수 있음

## 성능 비교

| 구분 | 원본 | 최적화 1 | 최적화 2 |
|------|------|----------|----------|
| **힙 메모리** | 가변 | 0 | 0 |
| **스택 메모리** | ~116B | ~1MB | ~100B |
| **루프 횟수** | 3번 | 3번 | 2번 |
| **함수 호출** | 많음 | 적음 | 최소 |
| **예측 가능성** | 중 | 높음 | 매우 높음 |

---

# 실무 코딩 패턴

## 1. 링버퍼 (Circular Buffer) - ADAS 센서 데이터

```cpp
#define BUFFER_SIZE 100

class RingBuffer {
private:
    int buffer[BUFFER_SIZE];
    int head = 0;
    int tail = 0;
    
public:
    void push(int data) {
        buffer[head] = data;
        head = (head + 1) % BUFFER_SIZE;  // 순환
    }
    
    int pop() {
        int data = buffer[tail];
        tail = (tail + 1) % BUFFER_SIZE;
        return data;
    }
    
    bool isEmpty() {
        return head == tail;
    }
    
    bool isFull() {
        return ((head + 1) % BUFFER_SIZE) == tail;
    }
};
```

## 2. 상태 머신 (State Machine) - 제어 로직

```cpp
enum State {
    IDLE,
    PROCESSING,
    ERROR
};

State currentState = IDLE;

void update() {
    switch(currentState) {
        case IDLE:
            // 초기화 로직
            if(startCondition) {
                currentState = PROCESSING;
            }
            break;
            
        case PROCESSING:
            // 처리 로직
            if(errorCondition) {
                currentState = ERROR;
            } else if(doneCondition) {
                currentState = IDLE;
            }
            break;
            
        case ERROR:
            // 에러 처리
            if(recoveryCondition) {
                currentState = IDLE;
            }
            break;
    }
}
```

## 3. 고정소수점 연산 (부동소수점 회피)

```cpp
// float 대신 정수 연산 (더 빠름)
#define SCALE 1000

// 1.234 m/s를 표현
int velocity_fixed = 1234;

// 2배 계산: 1.234 * 2 = 2.468
int result = (velocity_fixed * 2000) / SCALE;

// 실수로 변환해서 출력
double velocity_real = (double)velocity_fixed / SCALE;
printf("%.3f m/s\n", velocity_real);  // 1.234 m/s
```

## 4. 메모리 풀 (Memory Pool)

```cpp
#define POOL_SIZE 100

template<typename T>
class MemoryPool {
private:
    T pool[POOL_SIZE];
    bool used[POOL_SIZE] = {false};
    
public:
    T* allocate() {
        for(int i = 0; i < POOL_SIZE; i++) {
            if(!used[i]) {
                used[i] = true;
                return &pool[i];
            }
        }
        return nullptr;  // 풀이 가득 참
    }
    
    void deallocate(T* ptr) {
        int index = ptr - pool;
        if(index >= 0 && index < POOL_SIZE) {
            used[index] = false;
        }
    }
};
```

## 5. 비트 필드 활용

```cpp
// 레지스터 제어용 구조체
struct ControlRegister {
    uint32_t enable : 1;      // 1비트
    uint32_t mode : 2;        // 2비트
    uint32_t speed : 3;       // 3비트
    uint32_t reserved : 26;   // 26비트
};

// 사용 예
ControlRegister reg;
reg.enable = 1;
reg.mode = 2;
reg.speed = 5;
```

---

# 임베디드/ADAS 코딩 원칙

## 1. 메모리 사용 원칙

```cpp
// ✅ 스택 메모리 (지역 변수)
int buffer[100];           // 빠르지만 크기 제한

// ✅ 정적 메모리 (전역/static)
static int largeBuffer[10000];  // 큰 배열

// ❌ 힙 메모리 (동적 할당)
int* ptr = new int[100];   // 금지!
```

## 2. 시간 복잡도 원칙

```cpp
// ✅ O(1) - 최고
array[index] = value;

// ✅ O(n) - 허용
for(int i = 0; i < n; i++) { }

// ⚠️ O(n²) - 가능하면 회피
for(...) for(...) { }

// ❌ O(2^n) - 금지
재귀 함수 (스택 오버플로우 위험)
```

## 3. 안전성 원칙

```cpp
// ✅ 경계 체크
if(index >= 0 && index < SIZE) {
    array[index] = value;
}

// ✅ 초기화 명확히
int count = 0;  // 반드시!

// ✅ const 활용
const int MAX = 100;
const int* ptr;  // 값 변경 불가
int* const ptr;  // 포인터 변경 불가
```

## 4. MISRA C++ 핵심 규칙

### 필수 규칙

```cpp
// ✅ 모든 변수는 초기화
int count = 0;

// ✅ const 적극 사용
const int MAX_SIZE = 100;

// ✅ 명시적 타입 변환
int x = static_cast<int>(3.14);

// ✅ nullptr 사용 (NULL 대신)
int* ptr = nullptr;

// ✅ 범위 기반 for문 사용
for(const auto& item : container) { }
```

### 금지 규칙

```cpp
// ❌ goto 문
goto label;

// ❌ 암묵적 타입 변환
double x = 10 / 3;  // int → double

// ❌ 매직 넘버
if(speed > 120) { }  // 120이 무엇인지 불명확

// ✅ 상수로 정의
const int MAX_SPEED = 120;
if(speed > MAX_SPEED) { }
```

---

# 취업 준비 체크리스트

## 필수 개념

- [ ] 동적 메모리 할당 최소화 (new/delete 회피)
- [ ] STL 사용 시 정적 크기 (`<array>`, 알고리즘 함수)
- [ ] `memset`, `memcpy` 등 C 함수 활용
- [ ] 비트 연산 숙달
- [ ] `const`, `static`, `volatile` 이해
- [ ] 시간 복잡도 O(n) 이하 유지
- [ ] 경계 조건 체크 습관화
- [ ] MISRA C++ 규칙 숙지

## 실무 기술

- [ ] Kalman Filter (센서 융합)
- [ ] PID Control (제어 알고리즘)
- [ ] CAN 통신 (자동차 네트워크)
- [ ] AUTOSAR (자동차 소프트웨어 표준)
- [ ] 링버퍼 구현
- [ ] 상태 머신 패턴
- [ ] 고정소수점 연산
- [ ] 메모리 풀 관리

## 코딩 테스트 대비

- [ ] 포인터 완벽 이해
- [ ] 배열과 포인터 관계
- [ ] Algorithm 라이브러리 주요 함수
- [ ] 문자열 처리 (C 스타일)
- [ ] 비트 마스킹
- [ ] 시간/공간 복잡도 분석

---

# 추천 학습 자료

## 임베디드 C++ 필수 개념

1. **메모리 레이아웃**: Stack, Heap, BSS, Data, Text
2. **포인터 & 배열**: 완벽 숙지
3. **비트 연산**: 레지스터 제어
4. **volatile 키워드**: 하드웨어 레지스터 접근
5. **constexpr**: 컴파일 타임 최적화

## ADAS 관련

1. **Kalman Filter**: 센서 융합
2. **PID Control**: 제어 알고리즘
3. **CAN 통신**: 자동차 네트워크
4. **AUTOSAR**: 자동차 소프트웨어 표준

## 참고 도서

- **Effective C++** (Scott Meyers)
- **Embedded C++ Programming** (Michael Barr)
- **MISRA C++:2008** (Guidelines)

---

# 마무리

이 문서는 백준 1157번 문제 분석을 시작으로 포인터의 핵심 개념을 이해하고, 임베디드/ADAS 실무에서 필요한 코딩 기법까지 다루었습니다.

**핵심 요약**:
1. 포인터는 주소를 저장하는 변수
2. 포인터 뺄셈 = 인덱스 계산
3. 배열의 연속성이 핵심
4. 임베디드에서는 메모리 예측 가능성이 중요
5. ADAS에서는 실시간성과 안전성이 최우선

**다음 단계**:
- 더 많은 백준 문제로 연습
- STM32/Arduino 프로젝트에 적용
- MISRA C++ 가이드라인 학습
- 실제 레이더/센서 데이터 처리 구현

---

*작성일: 2026년 2월 15일*
*작성자: Deepblue*
