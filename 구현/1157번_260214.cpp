//1157번문제 단어 공부
//알파벳 대소문자로된 단어가 주어지면 이 단어에서 가장 많이 사용된 알파벳이 무엇인지 알아내는 프로그램 작성.
//입력 : 단어 입력
//출력 : 가장 많이 사용된 알파벳이 무엇인지 출력. 대문자로 출력. 단, 가장 많이 사용된 알파벳이 여러개인 경우에는 ?를 출력
// algorithm공부하기 : fill, max_element, distance
#include <iostream>
#include <string> //string, map, vector 등등 동적할당 회피
#include <algorithm>
using namespace std;

int main() {

    string word; //단어 입력받기 위한 배열(**임베디드 관점에서 입력을 제한 하는게 좋다)
    cin.width(1000000); //입력받을 수 있는 최대 글자 수 설정(**임베디드) //setw(1000000)로도 가능하지만 헤더를 추가해야한다 <iomanip>
    cin >> word; //<cstdio> or <stdio.h>헤더를 포함하여 scanf사용 가능 입력 속도를 올릴때 사용.
    int maxCount = 0;
    
    
    int alphabet[26] = {0,}; //알파벳의 개수를 세기 위한 배열. 26개로 초기화 **정적 배열**
    const int ALPHABET_SIZE = 26; //알파벳 개수 상수로 정의(**임베디드)
    //fill(alphabet, alphabet + 26, 0); //배열 초기화 => 초기화 2번 중복 제외해도 됨
    //fill대신 memset(alphabet, 0, sizeof(alphabet)); //배열 초기화 => 초기화 2번 중복 제외해도 됨

    for(char c : word) {
        if(isupper(c)) {
            alphabet[c - 'A']++; //대문자일 경우 해당 알파벳의 인덱스에 1 증가
        } else {
            alphabet[c - 'a']++; //소문자일 경우 해당 알파벳의 인덱스에 1 증가
        }
    }
    /*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
    for(int i=0; word[i] != '\0'; i++){
        char c = toupper(word[i]);
        alphabet[c - 'A']++; //대문자와 소문자 모두 같은 인덱스에 개수를 세도록 함.
    }*/
    //ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
    auto maxIndex = distance(alphabet, max_element(alphabet, alphabet + 26)); //가장 많이 나온 알파벳의 인덱스 찾기
    //int *max_element(int *first, int *last) : 범위에서 가장 큰 요소를 찾는 함수. 
    //distance : 두 반복자 사이의 거리를 반환하는 함수.
    //  max_element : 범위에서 가장 큰 요소를 찾는 함수
    //a와 A를 구분할필요 없다 어차피 마지막 출력만 대문자로 출력하면 된다. 그래서 대문자와 소문자 모두 같은 인덱스에 개수를 세도록 함.
    maxCount = alphabet[maxIndex];
    int cntMax = 0; //가장 많이 나온 알파벳의 개수 세기 위한 변수
    /*ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
     // 최댓값 찾기 (algorithm 없이)
    int maxCount = 0;
    int maxIndex = 0;
    for(int i = 0; i < 26; i++) {
        if(alphabet[i] > maxCount) {
            maxCount = alphabet[i];
            maxIndex = i;
        }
    }
        ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
    */
    //ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ수정전 1차 코드
    /*for(int i = 0; i<26; i++){
        if(alphabet[i] == maxCount && i != maxIndex){
            cout << '?';
            
        } else if(alphabet[i] == maxCount){
            cout << (char)(i + 'A'); //가장 많이 나온 알파벳을 대문자로 출력
        }
    }
    return 0;*/
    //ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
    for (int i=0; i < ALPHABET_SIZE; i++) {
        if(alphabet[i] == maxCount) {
            cntMax++;
        }
    }
     if(cntMax > 1) {
        cout << '?';
    } else {
        cout << (char)(maxIndex + 'A'); //가장 많이 나온 알파벳을 대문자로 출력 
    }

    
    //각 자리의 char를 배열로 매칭해야 한다.
    //그리고 가장 많이 나온 것을 확인하고 대문자로 출력한다.




}
//1차시도에서 문제 발생 : aabb를 입력했을때 A?라는 출력값이 나오게 된다. 정답 = ?이 나와야 한다
