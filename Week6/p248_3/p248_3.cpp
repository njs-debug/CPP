#include <iostream>

struct MyTime {
    int hour;
    int min;
};

MyTime addTime(MyTime t1, MyTime t2){
    MyTime result;
    result.min = t1.min + t2.min;
    result.hour = t1.hour + t2.hour + (result.min / 60);
    result.min %= 60;
    return result;
}

void addTime (MyTime t1, MyTime t2, MyTime& t3){
    t3.min = t1.min + t2.min;
    t3.hour =  t1.hour + t2.hour + (t3.min / 60);
    t3.min %= 60;    
}

void addTime (MyTime t1, MyTime t2, MyTime* pt){
    pt->min = t1.min + t2.min;
    pt->hour =  t1.hour + t2.hour + (pt->min / 60);
    pt->min %= 60;
}

int main() {
    MyTime time1 = {1, 40};
    MyTime time2 = {2, 30};
    MyTime time3 = addTime(time1, time2);
    MyTime time4;
    addTime(time1, time2, time4);
    MyTime time5;
    addTime(time1, time2, &time5);

    return 0;
}

