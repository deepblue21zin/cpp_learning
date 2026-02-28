//2563번 색종이
//가로 세로 크기 100 정사각형. 가로 세로 10인 검은색 색종이
//입력 : 색종이의 수, 다음줄부터 각각 색종이의 왼쪽 모서리 좌표값

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main(){

    //변수 : 색종이수 N <= 100 좌표 : 0<= x, y <=100
    int N,x,y;
    
    cin >> N;
      
    //알고리즘 종이의 갯수 만큼의 넓이에서 겹치는 부분을 제외해준다.
    //(start_x, start_y)부터 가로 세로 10칸씩 1로 칠하기 기가막히네 생각도 못했다.
    //xs[a] - xs[b] >10이면 인걉침, 아니면 겹침
    //ys[a] - ys[b] > 10 이면 안겹침
    /*int yarr[N][N];
    int xarr[N][N];
    int etc_sum = 0;
    for(int i =0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(xs[i] - xs[j] < 10){
                xarr[i][j] = xs[i] - xs[j];
                yarr[i][j] = ys[i] - ys[j];
            }
        }
    }*/
    int paper[101][101] = {};
    for (int i = 0; i < N; i++){
        cin >> x >> y;
        for(int r = x; r < x + 10; r++){
            for (int c = y; c < y+10; c++){
                paper[r][c] = 1;
            }
        }
    }
    int total_area = 0;

    for (int i = 0; i < 100; i++) {       // x 좌표 순회
        for (int j = 0; j < 100; j++) {   // y 좌표 순회
            if (paper[i][j] == 1) {       // 칠해진 부분이라면
                total_area++;
            }
        }
    }

    cout << total_area << "\n";


    return 0;
}