//10814번 나이순 정렬
//age = (1~100)

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdint>
#include <cstdio> 

using namespace std;
namespace {
  constexpr int MAX_mem = 100000;
  constexpr int MAX_age = 100;

}
struct Person{
    string name;
    int age;
};
static bool cmp(const Person& a, const Person& b){
    
    return a.age < b.age;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Person p;

    int N;
    cin >> N;
    vector<Person> v;
    v.reserve(N);
    

    for(int i=0; i<N; i++){
        
        
        cin >> p.age >> p.name;
        v.push_back(p);
    }

    stable_sort(v.begin(), v.end(), cmp);

    for (const auto& s : v) {
        cout << s.age << " " << s.name << '\n';
    }
    return 0;

}

