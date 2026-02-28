//11652번 카드

#include <iostream>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#ifdef DEBUG
    #define DLOG(x) do { std::cerr << x << '\n'; } while (0)
#else
    #define DLOG(x) do {} while (0)
#endif


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int N; // N (1 ≤ N ≤ 100,000)
    cin >> N;
    

    vector<long long> v; 
    v.reserve(N);

    for(int i = 0; i < N; i++){
        long long integer;
        cin >> integer;
        v.push_back(integer);
    }

    stable_sort(v.begin(), v.end());

    
    int current_cnt = 1;
    int max_cnt = 1;
    long long max_integer = v[0];

    for(int i=1; i < N; i++){
        if (v[i] == v[i-1]){
            current_cnt++;
        }else{
            current_cnt = 1;
        }
        if(current_cnt > max_cnt){
            max_cnt = current_cnt;
            max_integer = v[i];

        }
    }

    cout << max_integer << '\n';
    
    return 0;
}