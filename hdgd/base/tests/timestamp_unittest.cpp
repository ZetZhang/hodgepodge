#include <iostream>
#include <cassert>
#include "hdgd/base/timestamp.h"

using namespace hdgd;

void checkByValue(Timestamp t) {
    Timestamp vT(t);
    assert(t == vT);
    vT = Timestamp::now();
    assert(t != vT);
}

void checkByConstReference(const Timestamp &t) {
    Timestamp crt(t);
    assert(t == crt);
    crt = Timestamp::now();
    assert(t != crt);
}

void checkForOperatorOverloading() {
    //Timestampeqt
}

void checkForTimeGetting() {

}

void checkForTimeOutputting() {

}

void otherCheck() {

}

int main(int argc, const char *argv[])
{
    //hdgd::Timestamp s, j, t;
    //s = hdgd::Timestamp::now();
    //std::cout << s.getNanoSecondsSinceEpoch() << std::endl;
    //j = hdgd::Timestamp::now();
    //std::cout << j.getNanoSecondsSinceEpoch() << std::endl;
    //t = hdgd::AddTime(j, 3.5f);
    //std::cout << t.getNanoSecondsSinceEpoch() << std::endl;
    //std::cout << hdgd::TimeDifference(t, j) << std::endl;
    //std::cout << t.toFormattedString() << std::endl;
    //std::cout << t.toString() << std::endl;

    hdgd::Timestamp time(Timestamp::now());
    checkByValue(time);
    checkByConstReference(time);
    return 0;
}
