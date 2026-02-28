#include <bits/stdc++.h>
using namespace std;

static bool cmp(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> v;
    v.reserve(N);

    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        v.push_back(std::move(s));
    }

    sort(v.begin(), v.end(), cmp);

    // sort 이후에만 중복 제거 가능
    v.erase(unique(v.begin(), v.end()), v.end());

    for (const auto& s : v) {
        cout << s << '\n';
    }
    return 0;
}