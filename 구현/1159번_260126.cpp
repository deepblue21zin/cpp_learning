
//1159번 농구 경기
//상근이는 내일 일본과 국가대표 친선 경기가 있는 날이다. 선발명단 작성해야함
//성의 첫글자가 같은 선수 5명을 선발하려고 한다. 
//if 성의 첫글자가 같은 선수가 5명보다 적다면 -> 기권
//입력 : 선수의 수 N, 다음 N개 줄에는 각 선수의 성이 주어진다.
//출력 : 선수 다섯명을 선발할 수 없는 경우 = PREDAJA를 출력, 선발 가능한 경우 = 사전순으로 성을 나열 출력



#include <iostream>
#include <list>
using namespace std;

int main(){

    int N = 0;
    //반복문으로 N만큼 입력 받아야함
    cin >> N;
    int count = 0;
    string name;
    int alphabet[26]={0, }; 
    while(true){
        
        cin >> name;
        
        count = count + 1;
    
        char firstChar = name[0];
        int index = firstChar - 'a';
        
        alphabet[index]++;
        if (count == N) break;

        
    }
    //입력받은 이름의 첫 글자를 뽑는 방법은?
    bool check = false;
    for(int i=0; i<26;i++){
        if(alphabet[i]>=5 ){
                char result = i + 'a';

                cout << result;
                check = true;
        }
        
    }
    if(check == false){

            cout << "PREDAJA" << endl;
    }
    return 0;





}
//배열을 활용해서 첫 글자를 뽑는다.
//항상 초기화하는 것을 잊지말자, 배열의 경우 int alphabet[26]={0, };으로 초기화
//bool check = false;를 통해서 성공과 실패를 정할 수 있다
//return 0;의 위치는 모든 로직이 끝난 후에 써야한다
/*if(check == false){
}이 부분이 for문안에 있어서 alphabet[i]를 다 체크 하기 전에 출력 되버린다*/
//출력이 옆으로 출력 될려면 cout << result;이렇게 해야한다. endl;을 해버리면 줄바꿈이 된다.