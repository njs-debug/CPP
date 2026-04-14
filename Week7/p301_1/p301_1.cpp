#include "p301_1.h"
#include <iostream>
#include <iomanip>

using namespace std;

void MyTime::convert(double duration){
    long long total_ms = static_cast<long long >(duration * 1000);
    hours = total_ms / 3600000;
    total_ms %= 3600000;
    minutes = total_ms / 60000;
    total_ms %= 60000;
    seconds = total_ms / 1000;
    milliseconds = total_ms % 1000;
}

void MyTime::print(){
    cout << setfill('0') << setw(2) << hours 
    << ":" << setw(2) << minutes << ":" << setw(2) 
    << seconds << ":" <<setw(3) << milliseconds << endl;
}

MyTime MyTime::add(MyTime t){
    MyTime result;
    double current_duration = hours * 3600 + minutes * 60 + seconds + milliseconds / 1000.0;
    double t_duration = t.hours * 3600 + t.minutes * 60 + t.seconds + t.milliseconds / 1000.0;
    result.convert(current_duration + t_duration);
    return result;
}

void MyTime::reset(){
    hours = 0;
    minutes = 0;
    seconds = 0;
    milliseconds = 0;
}

void MyTime::read(){
    cout << "시, 분, 초, 밀리초를 순서대로 입력하세요(예: 1 2 34 567): ";
    cin >> hours >> minutes >> seconds >> milliseconds;
}

int main(){
    MyTime t1, t2, t3;

    t1.read();

    t2.convert(3661.123);

    t3 = t1.add(t2);

    t3.print();

    t3.reset();
    t3.print();

    return 0;
}

