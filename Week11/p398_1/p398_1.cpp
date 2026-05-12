#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Sample {
    char* name;
    static int count;

public:
    Sample() {
        name = nullptr;
        count++;
    }

    Sample(const char* name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        count++;
    }

    Sample(const Sample& s) {
        this->name = new char[strlen(s.name) + 1];
        strcpy(this->name, s.name);
        count++;
    }

    ~Sample() {
        delete[] name;
        count--;
    }

    static void printCount() {
        cout << count << endl;
    }
};

int Sample::count = 0;

int main() {
    Sample a("sample");
    Sample b(a);
    
    Sample::printCount();
    
    return 0;
}