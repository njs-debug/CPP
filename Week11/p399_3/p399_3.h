#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Canvas {
    int width, height;
    vector<string> map;

public:
    Canvas(int w, int h) : width(w), height(h) {
        map.resize(height, string(width, ' '));
    }

    void clear() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) map[i][j] = ' ';
        }
    }

    void draw(int x, int y, string s) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            map[y][x] = s[0]; // 아이콘의 첫 글자만 표시
        }
    }

    void print() {
        system("cls"); // 화면 지우기 (Windows용)
        for (int i = 0; i < height; i++) {
            cout << map[i] << endl;
        }
    }
};

#endif