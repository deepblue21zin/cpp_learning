//10866 덱

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

#ifdef DEBUG
    #define DLOG(x) do { std::cerr << x << '\n'; } while (0)
#else
    #define DLOG(x) do {} while (0)
#endif
struct command {
    string S;
    int num;
};

struct Deque {
    static constexpr int CAP = 10000;
    int arr[CAP];
    int head;
    int tail;
    int sz;

    Deque(){
        head = 0;
        tail = 0;
        sz = 0;
    }

    void push_front(int x){
        if(sz == CAP) {
            return;
        }
        head = (head -1 +CAP) % CAP;
        arr[head] = x;
        sz++;
    }
    void push_back(int x){
        if(sz == CAP) return;
        arr[tail] = x;
        tail = (tail + 1) %CAP;
        sz++;
    }
    void pop_front(){
        if(sz == 0){
            cout << -1 << '\n';
        }else{
            cout << arr[head] << '\n';
            head = (head + 1) % CAP;
            sz--;
        }
        
        
    }
    void pop_back(){
        if(sz == 0){
            cout << -1 << '\n';
        
        }else{
            tail = (tail -1 + CAP)% CAP;
            cout << arr[tail] << '\n';
            sz--;
        }
        
    }
    int size(){
        return sz;
    }
    void front(){
        if(sz == 0){
            cout << -1 << '\n';
        }else{
            cout << arr[head] << '\n';
        }
    }
    int empty(){
        if(sz == 0){
            return 1;
        
        }else{
            return 0;
        }
    }
    void back(){
        if(sz == 0){
            cout << -1 << '\n';
        }else{
            int idx = (tail -1 + CAP) % CAP;
            cout << arr[idx] << '\n';
        }
    }

};

int main() {
    command cmd;
    Deque Dq;
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for(int i=0; i<N;i++){
        
        cin >> cmd.S;
        if (cmd.S == "push_front"){
            cin >> cmd.num;
            Dq.push_front(cmd.num);
            
        }else if(cmd.S == "pop_back"){
            Dq.pop_back();
            
        }else if(cmd.S == "size"){
            cout << Dq.size() << '\n';
        }else if(cmd.S == "front"){
            Dq.front();
        }else if(cmd.S == "empty"){
            cout << Dq.empty() << '\n';
        }else if(cmd.S == "back"){
            Dq.back();
        }else if(cmd.S == "push_back"){
            cin >> cmd.num;
            Dq.push_back(cmd.num);
        }else if(cmd.S == "pop_front"){
            Dq.pop_front();
        }

    }






    return 0;
}