#pragma once
#include <iostream>
#include <string>
#include "Canvas.h"
using namespace std;

#define DIM 40

class Monster {
    string name, icon;  // 몬스터 이름과 화면 출력용 아이콘
    int x, y, nItem;    // 현재 위치와 먹은 아이템 수
    
    // (1) 에너지를 저장하는 속성 추가
    int nEnergy;        

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }

    // (3) eat() 함수 수정
    void eat(int map[DIM][DIM]) {
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
            nEnergy += 8; // 아이템을 먹으면 에너지 8 증가
        } else {
            nEnergy -= 1; // 아이템을 먹지 못하면 에너지 1 감소
            if (nEnergy < 0) nEnergy = 0; // 에너지의 최솟값은 0
        }
    }

public:
    // (2) 생성자의 멤버 초기화 리스트를 이용해 nEnergy를 100으로 초기화
    Monster(string n = "나괴물", string i = "※", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) {}

    ~Monster() { cout << "\t" << name << icon << " 물러갑니다~~~\n"; }

    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
    
    void move(int map[DIM][DIM], int maxx, int maxy) {
        switch (rand() % 8) {
            case 0: y--; break;
            case 1: x++; y--; break;
            case 2: x++; break;
            case 3: x++; y++; break;
            case 4: y++; break;
            case 5: x--; y++; break;
            case 6: x--; break;
            case 7: x--; y--; break;
        }
        clip(maxx, maxy);
        eat(map);
    }

    // (4) print() 함수 수정: 현재 에너지 레벨(E: 값) 출력되도록 변경
    void print() { 
        cout << "\t" << name << icon << ":" << nItem << " E:" << nEnergy << endl; 
    }
};