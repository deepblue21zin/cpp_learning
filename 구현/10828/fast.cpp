//10828 스택

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
struct stack {
    int arr[10001];
    int Top;

    stack() {Top = -1;}

    void push(int x){
        if(Top == 10000) {
            return;
        }
        arr[++Top] = x;
        

    }
    void pop(){
        if(Top == -1){
            cout << -1 <<'\n';
            return;
        }else{
            cout << arr[Top] << '\n';
        } 
        Top--;
    }
    void top(){
        if(Top==-1){
            cout << -1 << '\n';
        }else{
            cout << arr[Top] << '\n';
        }
    }

    void empty() {
        if (Top == -1) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
    int size(){
        return Top + 1;
    }


};
int main(){

    command cmd;
    stack st;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> stack_v;
    
    for(int i=0; i<N;i++){
        
        cin >> cmd.S;
        if (cmd.S == "push"){
            cin >> cmd.num;
            st.push(cmd.num);
            
        }else if(cmd.S == "pop"){
            st.pop();
            
        }else if(cmd.S == "size"){
            cout << st.size() << '\n';
        }else if(cmd.S == "top"){
            st.top();
        }else if(cmd.S == "empty"){
            st.empty();
        }

    }



    return 0;

}