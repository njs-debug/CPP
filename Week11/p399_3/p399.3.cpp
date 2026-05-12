#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "p399_3.h"

using namespace std;

class Monster {
    string name, icon;
    int x, y, nEnergy;
    static int monsterCount; // 정적 멤버 변수

public:
    Monster(string n, string i, int px, int py, int e)
        : name(n), icon(i), x(px), y(py), nEnergy(e) {
        monsterCount++;
    }

    ~Monster() {
        monsterCount--;
    }

    void move() {
        x += rand() % 3 - 1;
        y += rand() % 3 - 1;
        nEnergy--; // 이동 시 에너지 감소
    }

    void eat() { nEnergy += 10; }

    void draw(Canvas& c) {
        c.draw(x, y, icon);
    }

    void print() {
        cout << name << icon << ":" << x << "," << y << " E:" << nEnergy << endl;
    }

    int getEnergy() { return nEnergy; }
    string getName() { return name; }

    static void printCount() {
        cout << "전체 몬스터의 수 : [" << monsterCount << "]" << endl;
    }
};

// 정적 변수 초기화
int Monster::monsterCount = 0;

class MonsterWorld {
    Canvas canvas;
    Monster** pMon;
    int nMon, maxMon;

public:
    MonsterWorld(int w, int h, int max) : canvas(w, h), maxMon(max), nMon(0) {
        pMon = new Monster * [maxMon];
        srand((unsigned int)time(NULL));
    }

    ~MonsterWorld() {
        for (int i = 0; i < nMon; i++) delete pMon[i];
        delete[] pMon;
    }

    void addMonster(Monster* m) {
        if (nMon < maxMon) pMon[nMon++] = m;
    }

    // 아사 처리 함수 (3번 문제 핵심)
    void checkStarvation() {
        for (int i = 0; i < nMon; ) {
            if (pMon[i]->getEnergy() <= 0) {
                cout << pMon[i]->getName() << " 아사" << endl;
                cout << "Monster 하나가 굶어죽습니다" << endl;
                // _getch(); // Windows-specific, removed for portability

                delete pMon[i];
                pMon[i] = pMon[nMon - 1]; // 마지막 몬스터를 빈 칸으로 이동
                nMon--;
            }
            else i++;
        }
    }

    void play() {
        while (true) {
            canvas.clear();
            for (int i = 0; i < nMon; i++) {
                pMon[i]->move();
                pMon[i]->draw(canvas);
            }

            canvas.print();
            for (int i = 0; i < nMon; i++) pMon[i]->print();
            Monster::printCount(); // 정적 함수 호출

            checkStarvation(); // 아사 체크 실행

            if (nMon <= 0) {
                cout << "모든 몬스터가 사망했습니다." << endl;
                break;
            }
        }
    }
};

int main() {
    MonsterWorld world(70, 20, 10);

    world.addMonster(new Monster("도깨비", "D", 10, 5, 20));
    world.addMonster(new Monster("고스트", "G", 30, 10, 15));
    world.addMonster(new Monster("좀비", "Z", 50, 15, 25));

    world.play();

    return 0;
}