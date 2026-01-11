#include <iostream>
using namespace std;

int main() {
    int a;
    cin >> a;
    if (a < 0 || a> 100){
        cout << "0~100사이의 값을 입력하세요" << endl;
        return 0;
    }
   
   
    if (90 <= a && a <= 100){
        cout << "A" << endl;
    } else if (80 <= a && a <= 89){
        cout << "B" << endl;

    }else if (70 <= a && a <= 79){
        cout << "C" << endl;

    }else if (60 <= a && a <= 69){
        cout << "D" << endl;
    }else {
        cout << "F" << endl;
    }
        

    return 0;
}


//1. 첫번째 시도 어떤 숫자를 넣어도 A가 나오는 문제 발생 => 원인이 뭘까 ? &&을 사용해야하는데 그냥 90<=a<=100으로 작성해서 그런것임 수정함
//2. 다음 문제 a의 범위 제한을 하지 않음 => 0~100사이의 값만 입력되도록 범위를 제한함
/*if (a < 0 || a> 100){
        cout << "0~100사이의 값을 입력하세요" << endl;
        return 0;
    }*/  //로 구현함 => 결과 안나옴
//3. cin >> a;를 까먹음. 
