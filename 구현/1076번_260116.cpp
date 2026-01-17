#include <iostream>
#include <string>
using namespace std;

int main(){

    //백준 1076번 문제 : 저항
    //저항의 색깔에 따른 저항값을 구하는 문제
    //처음 색 2개는 저항의 값, 마지막 색은 곱해야함.
    //입력 : color1  color2  color3
    string color1, color2, color3;
    cin >> color1 >> color2 >> color3;

    int value1 =0, value2 =0, value3=0; //각 색깔의 인덱스를 저장할 정수 변수 만들기

    //color의 종류 10개 저장(배열에 저장)
    string color[10] = {"black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "grey", "white"};

    for(int i = 0; i < 10; i++){
        if (color1 == color[i]){
            value1 = i;

        }
        if(color2 == color[i]){
            value2 = i;

        }
        if(color3 == color[i]){
            value3 =1;
            for(int j = 0; j< i; j++){
                value3 = 10 * value3;

            }
        }
    }
    long long result = 0;
    result = (value1 * 10+value2) * value3;
    cout <<result <<endl;
    
    

    return 0;







}