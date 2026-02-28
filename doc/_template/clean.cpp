/*clean.cpp “체크 5개”(고정)

constexpr로 매직넘버 제거

타입은 int32/int64를 최악값 계산으로 결정

큰 버퍼는 static/global 또는 “왜 vector 써도 되는지” 한 줄 근거

함수 2개로 분리(처리/계산)

주석 2줄: “왜 이 방식” + “Time/RAM”*/


// clean.cpp - BOJ XXXXX
// Embedded/ADAS style: deterministic memory, bounded loops, clear constants, safe bounds.
//
// Step0:
// CONSTS: (고정 크기/매직넘버 정리)
// TYPE: (최악값 1줄 계산 -> int32/int64 선택)
// MEM:  (주요 버퍼 bytes, local big array 금지 여부)

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <array>
#include <vector>

namespace {
using i32 = std::int32_t;
using i64 = std::int64_t;
using u8  = std::uint8_t;

#ifdef DEBUG
  #define DLOG(msg) do { std::cerr << msg << '\n'; } while (0)
#else
  #define DLOG(msg) do {} while (0)
#endif

// (선택) 범위 체크 헬퍼 - 필요할 때만 사용
inline bool in_range(const i32 v, const i32 lo, const i32 hi) {
    return (lo <= v) && (v <= hi);
}

// TODO: constexpr 상수들
// constexpr int kSize = ...;

// TODO: 정적 버퍼(필요할 때만)
// static u8 grid[...][...] = {0};

// TODO: helper functions (2~3개까지 권장)
// static void solve(...)
// static i32 calc(...)

} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // 1) 입력
    // 2) 처리
    // 3) 출력
    return 0;
}