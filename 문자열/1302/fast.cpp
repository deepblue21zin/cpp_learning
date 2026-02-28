//1302 베스트셀러

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

#ifdef DEBUG
    #define DLOG(x) do { std::cerr << x << '\n'; } while (0)
#else
    #define DLOG(x) do {} while (0)
#endif

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    unordered_map<string, int> freq; //순서가 없는 해시 테이블


    for(int i = 0; i < N;i++){
        string book;
        cin >> book;
        freq[book]++;
    }

    
    int max_val = 0;
    string max_word = "";
    for(auto const& [word, count] : freq){
        if(count > max_val || (count == max_val && word < max_word)){
            max_val = count;
            max_word = word;
        }
    }

    

    
    cout << max_word << '\n';
    return 0;
}