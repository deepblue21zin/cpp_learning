// BOJ 10828 스택 - corrected

#include <iostream>
#include <string>
using namespace std;

struct Stack {
    static constexpr int kCap = 10000; // 명령 최대 10000이면 충분
    int arr[kCap];
    int Top;

    Stack() : Top(-1) {}

    void push(int x) {
        if (Top == kCap - 1) return; // overflow 방어(문제에선 거의 의미없지만 안전)
        arr[++Top] = x;
    }

    int pop() {
        if (Top == -1) return -1;
        return arr[Top--];
    }

    int top() const {
        if (Top == -1) return -1;
        return arr[Top];
    }

    int empty() const {
        return (Top == -1) ? 1 : 0;
    }

    int size() const {
        return Top + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    Stack st;

    for (int i = 0; i < N; ++i) {
        string cmd;
        cin >> cmd;

        if (cmd == "push") {
            int x;
            cin >> x;
            st.push(x);
        } else if (cmd == "pop") {
            cout << st.pop() << '\n';
        } else if (cmd == "size") {
            cout << st.size() << '\n';
        } else if (cmd == "empty") {
            cout << st.empty() << '\n';
        } else if (cmd == "top") {
            cout << st.top() << '\n';
        }
    }

    return 0;
}