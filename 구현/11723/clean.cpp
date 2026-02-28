//11723 clean.cpp
//핵심: 20비트 비트마스크 + M(최대 3,000,000) 대응을 위한 빠른 입력/출력 버퍼링
// clean.cpp - BOJ 11723 집합
// 핵심: 20비트 비트마스크 + M(최대 3,000,000) 대응을 위한 빠른 입력/출력 버퍼링
#include <cstdint>
#include <cstdio> //고정 루틴
#include <iostream>
#include <string>

namespace { //고정 루틴
constexpr int kMaxElem = 20;
constexpr std::uint32_t kAllMask = (1u << kMaxElem) - 1u; //고정 루틴

// 임베디드식: 동적할당 최소화, 입력은 고정 버퍼 fread로 처리
struct FastScanner { //scanf나 cin보다 수십배 빠른 성능을 내기 위해 설계된 사용자 정의 입력 시스템
    static constexpr std::size_t kBufSize = 1u << 20; // 1MB 크기의 버퍼(u = unsigned int)
    char buf[kBufSize];
    std::size_t idx = 0;
    std::size_t size = 0;
//핵심원리 : 하드디스크나 네트워크에서 데이터를 1바이트씩 가져오는건 매우 느리다. 그래서 1MB라는 큰 바구니(buf)를 준비해 한꺼번에 담아오고, 메모리안에서만 커서를 움직이며 읽는 방식
//1u << 20 은 비트 연산으로 2^20즉 1MB
    inline char read_byte() { //바이트 읽기 함수read_byte
        if (idx >= size) { //바구니가 비었거나 다 읽었다면?
            size = std::fread(buf, 1, kBufSize, stdin); //새로 1MB를 채워옴
            idx = 0; //커서 다시 맨 앞으로
            if (size == 0) return 0; //더이상 읽을 데이터가 없으면 종료
        }
        return buf[idx++]; //바구니에서 한 글자 꺼내주고 커서를 한 칸 이동
    }

    inline bool read_int(int &out) { //정수 변환 함수(read_int) : 문자열로 된 숫자를 실제 정수로 바꾸는 과정
        char c = 0; //공백, 탭, 줄바꿈 등 무의미한 문자를 건너뜀
        do { c = read_byte(); } while (c && c <= ' ');
        if (!c) return false; //읽을게 없으면 실패 반환

        int val = 0; //숫자인 동안 계속 반복(공백 만나면 멈춤)
        while (c > ' ') {
            val = val * 10 + (c - '0'); //기존 값에 10을 곱하고 새 숫자를 더함
            c = read_byte();
        }
        out = val; //최종 결과를 out에 저장
        return true;
    }

    inline int read_word(char *out, const int cap) { //add, remove 같은 명령어를 읽는 함수
        //cap(capacity : buffer overflow 방지를 위한 제한)
        char c = 0; //앞쪽 공백 제거
        do { c = read_byte(); } while (c && c <= ' ');
        if (!c) return 0;

        int len = 0; //공백을 만나기 전까지 혹은 버퍼 크기(cap)를 넘기 전까지 읽음
        while (c > ' ' && len + 1 < cap) {
            out[len++] = c; //한 글자씩 저장
            c = read_byte();
        }
        out[len] = '\0'; //문자열의 끝을 알리는 NULL 문자 삽입(반드시)
        return len;
    }
};

inline std::uint32_t bit_of(const int x) {
    // x: 1..20 (입력 보장)
    return 1u << static_cast<unsigned>(x - 1);
}
} // namespace

int main() {
    FastScanner fs;

    int M = 0;
    if (!fs.read_int(M)) return 0;

    std::uint32_t S = 0;

    // check 출력만 모아서 한 번에 출력 (최대 3,000,000줄 => 약 6MB)
    std::string out;
    out.reserve(static_cast<std::size_t>(M) * 2u);

    char cmd[8]; // "toggle"(6) + '\0'
    for (int i = 0; i < M; ++i) {
        fs.read_word(cmd, static_cast<int>(sizeof(cmd)));

        // 첫 글자로 분기 (add/all 둘 다 'a'라서 두 번째 글자까지 확인)
        switch (cmd[0]) {
            case 'a': { // add / all
                if (cmd[1] == 'd') { // add
                    int x = 0; fs.read_int(x);
                    S |= bit_of(x);
                } else { // all
                    S = kAllMask;
                }
            } break;

            case 'r': { // remove
                int x = 0; fs.read_int(x);
                S &= ~bit_of(x);
            } break;

            case 'c': { // check
                int x = 0; fs.read_int(x);
                out.push_back((S & bit_of(x)) ? '1' : '0');
                out.push_back('\n');
            } break;

            case 't': { // toggle
                int x = 0; fs.read_int(x);
                S ^= bit_of(x);
            } break;

            case 'e': { // empty
                S = 0;
            } break;

            default:
                // 입력은 문제에서 보장하지만, 방어적으로 무시
                break;
        }
    }

    std::fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}