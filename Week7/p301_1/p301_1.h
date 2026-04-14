#ifndef p301_1.h
#define p301_1.h

class MyTime {
private:
    int hours;
    int minutes;
    int seconds;
    int milliseconds;

public:
    void convert(double duration);
    void print();
    MyTime add(MyTime t);
    void reset();
    void read();
};

#endif
