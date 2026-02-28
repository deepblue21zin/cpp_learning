// clean.cpp - BOJ 2563 색종이
// Embedded/ADAS style: deterministic memory, bounded loops, clear constants, safe bounds.

#include <iostream>
#include <cstdint>   // uint8_t //단순히 char나 short쓰지 않고 명확히 uint8_t사용
#include <algorithm> // std::min

namespace { //함수와 변수들이 이 파일 안에서만 보이고 외부에서는 접근할 수 없게 만든다. 임베디드에서 전역변수 충돌을 막는 매우 중요한 습관
constexpr int WBoardSize = 100; //배열 크기100을 상수로 정의, 컴파일 타임에 모든 메모리 계산이 끝나도록 했다.
constexpr int BPaperSize = 10;

// grid[x][y] : 0 or 1 (byte). 100*100 = 10,000 bytes.
static std::uint8_t grid[WBoardSize][WBoardSize] = {0}; //static 메모리 고정(스택 오버플로우 완전 차단)
//uint8_t 딱 1바이트 int 보다 1/4

inline int clamp_high(const int v, const int hi_exclusive) {
    // clamp to [0, hi_exclusive]
    if (v < 0) return 0;
    if (v > hi_exclusive) return hi_exclusive;
    return v;
} //inline 함수 : 간단한 로직인 clamp_high를 inline으로 선언하여 함수 호출 오버헤드 없앰
//clamp_high함수 : 입력 좌표가 음수이거나 100을 넘더라도 플로그램이 죽지 않고, 안전한 범위 내에서만 동작하도록 가둠


static void mark_paper_10x10(const int x, const int y) {
    // Safe bounds even if input is slightly out-of-range.
    const int x0 = clamp_high(x, WBoardSize);
    const int y0 = clamp_high(y, WBoardSize);

    const int x1 = std::min(x0 + BPaperSize, WBoardSize);
    const int y1 = std::min(y0 + BPaperSize, WBoardSize); //std::min : x0+10이 도화지 밖으로 나가지 않도록 한 번더 검증. 덕분에 배열 인덱스 에러가 발생하지 않는다


    for (int r = x0; r < x1; ++r) {
        for (int c = y0; c < y1; ++c) {
            grid[r][c] = 1U;
        }
    }
}

static int calc_area(void) {
    int area = 0;
    for (int r = 0; r < WBoardSize; ++r) {
        for (int c = 0; c < WBoardSize; ++c) {
            area += (grid[r][c] != 0U) ? 1 : 0;
        }
    }
    return area;
} //중복 면적 계산 로직을 고민할 필요없이, 도화지를 한 번만 훑는 (O(size^2))선형적인 시간 복잡도로 면적을 구함. 예측가능하게 만듦

} // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N = 0;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        int x = 0, y = 0;
        std::cin >> x >> y;
        mark_paper_10x10(x, y);
    }

    std::cout << calc_area() << '\n';
    return 0;
}