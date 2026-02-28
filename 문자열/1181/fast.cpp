//1181번 단어정렬
//N개의 단어가 들어오면 1. 길이가 짦은것부터, 2. 길이가 같으면 사전 순으로 정렬
//입력 : N개 주어짐(1<= N <= 20000), 다음부터 N개 단어 주어짐
//출력 : 조건에 맞게 단어 출력

#include <iostream>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#ifdef DEBUG
  #define DLOG(msg) do { cerr << msg << '\n'; } while (0)
#else
  #define DLOG(msg) do {} while (0)
#endif

namespace {
    constexpr uint32_t MAX_N = 20000;

    struct FastScanner {
        static constexpr size_t BufSize = 1u << 20;
        char buf[BufSize];
        size_t idx = 0;
        size_t size = 0;

        inline char read_byte(){
            if(idx >= size){
                size = fread(buf, 1, BufSize, stdin);
                idx = 0;
                if(size == 0) return 0;
            }
            return buf[idx++];
        }
        inline bool read_int(int &out) { //정수 변환 함수(read_int) : 문자열로 된 숫자를 실제 정수로 바꾸는 과정
            char c = read_byte(); //공백, 탭, 줄바꿈 등 무의미한 문자를 건너뜀
            while (c && c <= ' ') c = read_byte(); // 공백 건너뛰기
            if (!c) return false; //읽을게 없으면 실패 반환

            int val = 0; //숫자인 동안 계속 반복(공백 만나면 멈춤)
            while (c > ' ') {
                val = val * 10 + (c - '0'); //기존 값에 10을 곱하고 새 숫자를 더함
                c = read_byte();
                if(c==0) break;
            }
            out = val; //최종 결과를 out에 저장
            return true;
        }
        inline int read_word(char *out, const int cap) { //add, remove 같은 명령어를 읽는 함수
        //cap(capacity : buffer overflow 방지를 위한 제한)
            char c = read_byte(); //앞쪽 공백 제거
            while (c && c <= ' ') c = read_byte();
            if (!c) return 0;

            int len = 0; //공백을 만나기 전까지 혹은 버퍼 크기(cap)를 넘기 전까지 읽음
            while (c > ' ' && len + 1 < cap) {
                out[len++] = c; //한 글자씩 저장
                c = read_byte();
                if(c==0)break;
            }
            out[len] = '\0'; //문자열의 끝을 알리는 NULL 문자 삽입(반드시)
            return len;
        }
    };   
    
    

    inline std::uint32_t bit_of(const int x) {
    // x: 1..20 (입력 보장)
        return 1u << static_cast<unsigned>(x - 1);

    }
}
bool compare(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() < b.length(); // 1. 길이가 짧은 순
    }
    return a < b; // 2. 길이가 같으면 사전 순 (string 객체는 사전 순 비교를 지원함)
}

int main() {
    FastScanner fs;

    int N = 0;
    if (!fs.read_int(N)) return 0;

    vector<string> wordList;
    char temp[64];

    for (int i =0; i<N;i++){
        int len = fs.read_word(temp, sizeof(temp));
        if(len > 0){
            wordList.push_back(string(temp));
        }else{
            break;
        }
    }
    sort(wordList.begin(), wordList.end(), compare);

    string last = "";
    for(const auto& w : wordList){
        if(w == last) continue;
        cout << w << "\n";
        last = w;
    }
    return 0;





}