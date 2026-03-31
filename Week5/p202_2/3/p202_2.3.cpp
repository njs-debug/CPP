#include <iostream>
#include "p202_2_3.hpp"

using namespace std;

void checkMap(int map[5][5]) {
    bool found = false;

    for (int i = 0; i < 5; i++) {
        int sum = 0;
        for (int j = 0; j < 5; j++){
            sum += map[i][j];
        }
        if (sum ==0) {
            cout << "가로" << i << "번째 행이 모두 0입니다." << endl;
            found = true;
        }
        else if (sum == 5) {
            cout << "가로" << i << "번째 행이 모두 1입니다." << endl;
            found = true;
        }
    }

    for (int j = 0; j < 5; j++) {
        int sum = 0;
        for (int i = 0; i < 5; i++){
            sum += map[i][j];
        }
        if (sum ==0) {
            cout << "세로" << j << "번째 열이 모두 0입니다." << endl;
            found = true;
        }
        else if (sum == 5) {
            cout << "세로" << j << "번째 열이 모두 1입니다." << endl;
            found = true;
        }
    }

    int diag1Sum = 0;
    for (int i = 0; i < 5; i++) {
        diag1Sum += map[i][i];
    }
    if (diag1Sum == 0) {
        cout << "대각선 (\\)이 모두 0입니다." << endl;
        found = true;
    }
    else if (diag1Sum == 5) {
        cout << "대각선 (\\)이 모두 1입니다." << endl;
        found = true;
    }

    int diag2Sum = 0;
    for (int i = 0; i < 5; i++) {
        diag2Sum += map[i][4 - i];
    }
    if (diag2Sum == 0) {
        cout << "대각선 (/)이 모두 0입니다." << endl;
        found = true;
    }
    else if (diag2Sum == 5) {
        cout << "대각선 (/)이 모두 1입니다." << endl;
        found = true;
    }

    if (!found) {
        cout << "모두 0이거나 1인 줄이 없습니다," << endl;
    }
}

int main() {
    int map[5][5] = {
        {1, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1}
    };

    checkMap(map);

    return 0;
}
