#include <iostream>
#include <iomanip>

using namespace std;

// 1. 클래스 선언부
class MyTime {
private:
    int hours;
    int minutes;
    int seconds;
    int milliseconds;

public:
    // [1번 문제] 기본 생성자 (디폴트 매개변수 사용)
    MyTime(int h = 0, int m = 0, int s = 0, int ms = 0)
        : hours(h), minutes(m), seconds(s), milliseconds(ms) {
    }

    // [2번 문제] double형 시간을 받는 중복 생성자 (초 단위 실수 입력)
    MyTime(double duration) {
        long long total_ms = static_cast<long long>(duration * 1000);
        hours = total_ms / 3600000;
        total_ms %= 3600000;
        minutes = total_ms / 60000;
        total_ms %= 60000;
        seconds = total_ms / 1000;
        milliseconds = total_ms % 1000;
    }

    void convert(double duration);
    void print();
    MyTime add(MyTime t);
    void reset();
    void read();
};

// 2. 클래스의 멤버 함수 구현부
void MyTime::convert(double duration) {
    long long total_ms = static_cast<long long>(duration * 1000);
    hours = total_ms / 3600000;
    total_ms %= 3600000;
    minutes = total_ms / 60000;
    total_ms %= 60000;
    seconds = total_ms / 1000;
    milliseconds = total_ms % 1000;
}

void MyTime::print() {
    cout << setfill('0') << setw(2) << hours 
         << ":" << setw(2) << minutes << ":" << setw(2) 
         << seconds << ":" << setw(3) << milliseconds << endl;
}

MyTime MyTime::add(MyTime t) {
    MyTime result;
    double current_duration = hours * 3600 + minutes * 60 + seconds + milliseconds / 1000.0;
    double t_duration = t.hours * 3600 + t.minutes * 60 + t.seconds + t.milliseconds / 1000.0;
    result.convert(current_duration + t_duration);
    return result;
}

void MyTime::reset() {
    hours = 0;
    minutes = 0;
    seconds = 0;
    milliseconds = 0;
}

void MyTime::read() {
    cout << "시, 분, 초, 밀리초를 순서대로 입력하세요(예: 1 2 34 567): ";
    cin >> hours >> minutes >> seconds >> milliseconds;
}

// 3. 메인 함수
int main() {
    // 1번 문제 확인: 매개변수 없이 객체 생성 (0으로 초기화됨)
    MyTime t1;
    cout << "t1 (기본 생성자): ";
    t1.print();

    // 2번 문제 확인: double 값을 전달하여 객체 생성
    // 기존에는 t2.convert(3661.123); 를 호출했지만, 
    // 이제는 객체를 만들면서 바로 값을 넣을 수 있습니다!
    MyTime t2(3661.123); 
    cout << "t2 (double 생성자 적용): ";
    t2.print();

    // 두 시간 더하기 테스트
    MyTime t3;
    t1.read(); // 값을 입력받음
    t3 = t1.add(t2);

    cout << "t1과 t2를 더한 시간: ";
    t3.print();

    return 0;
}