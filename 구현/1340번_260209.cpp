//1340번 연도 진행바 문제
//연도 진행바, 이번 해가 얼마나 지났는지를 보여주는 것
#include <iostream>
#include <iomanip> //소수점 자리수 조절 라이브러리
#include <string> //문자열 라이브러리
using namespace std;
bool Leap_year(int y) {
        return (y%4 == 0 && y % 100 !=0 ) || (y % 400 == 0);
}

int main() {

    //연도 입력 받기 Month DD, YYYY HH:MM과 같이 주어진다. 
    //Month는 1~12월, DD는 1~31일, YYYY는 연도, HH는 0~23시, MM은 0~59분
    int day, year, hour, minute;
    char colon, comma;
    string month; //월은 문자열로 받기
    

    cin >> month >> day >> comma >> year >> hour >> colon >> minute;
    //몇 퍼센티지 인지 출력하기 year = 365일, 하루 = 24시간, 1시간 = 60분
    //총 퍼센티지는 1년 = 365 * 24 * 60

    long long total_minutes = 0;
    if(Leap_year(year)){
        total_minutes = 366 * 24 * 60;
    } else {
        total_minutes = 365 * 24 * 60;
    }
    //삼항 연산자 (?: ) 사용 가능
    //int total_days = Leap_year(year) ? 366 : 365 ;
    // long long total_minutes = (long long)total_days * 24 * 60; //형변환 주의
    //장점 : 가동성과 코드의 간결함 , 초기화와 안정성 확보 가능
    int passed_minutes = 0;
    int monthInt = 0; //월을 숫자로 변환하기 위한 변수

    //월 = 문자 => 숫자로 구분 필요, 1월 1일 부터 현재까지 흐른 시간 한달을 1,3,5,7,8,10,12 = 31일, 2월 29일, 나머지 = 30일
    //시간은 24-현재시간, 분 = 60분-현재분 으로 계산
    //아이디어 어떻게 구분해서 현재까지의 일의 수를 구할 수 있을까?
    string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; //인덱스 1~12월 까지 매칭
    //산업에서의 배열 팁 : 데이터는 메모리에 1열로 쭉 나열되어 있지만, 우리가 [i][0] 이라고 부르는 순간 컴퓨터가 알아서 i번째 묶음의 첫 번째 칸으로 점프해서 감.
    //순수 2차원 배열 임베디드에서 메모리를 효율적으로 쓸 때 가장 선호하는 방식이다. 
    
    for (int i=0;i<12;i++){
        if(months[i] == month){
            monthInt = i +1;
            break;
        }
    }
    for (int m = 1; m < monthInt ; m++) {  //'0'을 빼서 문자형을 정수형으로 변환('0' = 48)
        //주의 string에서 char를 뺼 수 없다. month는 string이므로 month - '0'은 불가능
        if (m == 1 || m == 3 || m ==5 || m == 7 || m == 8 || m == 10 || m == 12) {
            passed_minutes += 31 * 24 * 60;
        } else if (m == 2) {
            passed_minutes += (Leap_year(year) ? 29 : 28) * 24 * 60;

        } else {
            passed_minutes += 30 * 24 * 60;
        }
        
    }
    //지금까지 지난 일수 더하기
    passed_minutes += (day-1) * 24 * 60;  //1월 1일 00:00 이라면 지난 시간은 0분 이어야 한다.
    //지금까지 지난 시간 더하기
    passed_minutes += hour * 60;
    //지금까지 지난 분 더하기
    passed_minutes += minute;
    //cout << ((double)passed_minutes / total_minutes) * 100 << endl; //double형으로 해야 소수점까지 정확히 나온다.
    cout << fixed << setprecision(9) << ((double)passed_minutes / total_minutes) * 100 << endl; //소수점 9자리까지 출력
    return 0;

    




}
//윤년 체크 함수 빠짐
//