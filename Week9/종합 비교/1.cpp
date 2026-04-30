#include <iostream>
#include <string>

using namespace std;

class Complex {
public:
    double real, imag;

    // 생성자
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 출력 함수 (라벨을 받아서 함께 출력)
    void print(const string& label) const {
        cout << label << " = " << real << " + " << imag << "i\n\n";
    }

    // 3. 멤버 함수, void 반환, 참조 전달
    // c.add3(a, b) 형태로 호출하여 c(this)에 결과를 저장합니다.
    void add3(const Complex& a, const Complex& b) {
        this->real = a.real + b.real;
        this->imag = a.imag + b.imag;
    }

    // 4. 멤버 함수, return 반환, 참조 전달
    // c = a.add4(b) 형태로 호출하여 자기 자신(a)과 매개변수(b)를 더한 새 객체 반환
    Complex add4(const Complex& b) const {
        return Complex(this->real + b.real, this->imag + b.imag);
    }

    // 5. 연산자 오버로딩
    // c = a + b 형태로 직관적인 사용 가능
    Complex operator+(const Complex& b) const {
        return Complex(this->real + b.real, this->imag + b.imag);
    }
};

// 1. 일반 함수, void 반환, 참조 전달
// 결과를 세 번째 인자 c(참조)에 직접 저장합니다.
void add1(const Complex& a, const Complex& b, Complex& c) {
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
}

// 2. 일반 함수, return 반환, 값 전달
// a, b가 값으로 복사되어 전달되며, 더한 결과를 새 객체로 반환합니다.
Complex add2(Complex a, Complex b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}


int main() {
    Complex a(1, 2);
    Complex b(3, 4);
    Complex c;

    cout << "초기값 a = 1 + 2i\n";
    cout << "초기값 b = 3 + 4i\n\n";

    cout << "1. 일반 함수, void, 참조 전달\n";
    add1(a, b, c);
    c.print("c");

    cout << "2. 일반 함수, return, 값 전달\n";
    c = add2(a, b);
    c.print("c");

    cout << "3. 멤버 함수, void, 참조 전달\n";
    c = Complex(0, 0); // c 초기화
    c.add3(a, b);
    c.print("c");

    cout << "4. 멤버 함수, return, 참조 전달\n";
    c = a.add4(b);
    c.print("c");

    cout << "5. 연산자 오버로딩\n";
    c = a + b;
    c.print("c");

    return 0;
}