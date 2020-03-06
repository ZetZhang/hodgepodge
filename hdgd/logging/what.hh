#include <iostream>
#include <string>
#include <cstring>
#include <utility>
#include <cstdarg>
#include <sstream>

class T
{
public:
    void test(std::string s) {
        std::cout << "string" << std::endl;
    }
    void test(char *s) {
        std::cout << "char *" << std::endl;
    }
};

template <size_t SIZ>
class TT
{
public:
    //TT() { std::cout << "construction" << std::endl; }
    void operator()(int i) {
        std::cout << "operator" << std::endl;
    }
    int operator()() {
        return 1;
    }
    static void op() {
        std::cout << "op" << std::endl;
    }
    size_t size() {
        return sizeof(buffer);
    }
private:
    char buffer[SIZ + 5];
};

class TTT
{
public:
    TTT() : temp("fuck") { if (!strlen(temp)) std::cout << "fuck" << std::endl; }
    int operator()(int i) {
        return i * i;
    }
private:
    char temp[10];
};

void temp1(const char *buf) {
    std::cout << buf << std::endl;
}

void list(const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    std::cout << va_arg(argList, int) << std::endl;
    va_end(argList);
}

template<typename T>
class f
{
public:
    virtual void what() = 0;
    //virtual std::ostream& operator<<(std::ostream &os, const T&) = 0;
    virtual ~f() { std::cout << "f destructor" << std::endl; }
};

class ffff
{
public:
    virtual ~ffff() { std::cout << "ffff destrcutor" << std::endl; }
};

class ff : public f<ff>, public ffff
{
public:
    ff() : _value("what the fuck") {}
    void what()  {
        std::cout << "f: -> :ff" << std::endl;
    }
    friend std::ostream& operator<<(std::ostream &os, const ff &x) {
        os << x._value;
        return os;
    }
    std::string _value;
    ~ff() { std::cout << "ff destructor" << std::endl; }
};

//template<typename T>
//class fff : public f<T>
//{
//public:
    //void what() {
        //std::cout << "fff" << std::endl;
    //}
//};

class A
{
public:
    // 多继承，必须有一个是虚继承，否则将无法
    virtual void At() = 0;
    //virtual ~A() { std::cout << "A" << std::endl; }
    virtual ~A() = default;
};

class AA
{
public:
    virtual void AAt() = 0;
    ~AA() { std::cout << "AA" << std::endl; }
};

template<typename T>
class need
{
public:
    template<typename o>
    friend std::ostream& operator<<(std::ostream &os, const need<o>&);
private:
};

template<typename T>
std::ostream& operator<<(std::ostream &os, const need<T>&x) {
    // friend class `ToString`
    os << "\" " << T::toString() << " \"";
    //os << "\" " << ToString(x) << " \"";
    return os;
}

class AAA : public A, public AA
{
public:
    AAA() : _value(12) {}
    void At() { std::cout << "At" << std::endl; }
    void AAt() { std::cout << "AAt" << std::endl; }
    static std::string toString() { return std::string("this is about AAA : "/* + _value*/); }
    ~AAA() { std::cout << "AAA" << std::endl; }
    static need<AAA> output();
    int _value;
};

int main(int argc, const char *argv[])
{
    T s;
    std::string ok("t");
    char ok1[3] = "aa";
    s.test(ok);
    s.test(ok1);
    s.test("ss");
    const char *str[2] = { "A", "B" };
#define conn(A, B) (A B)
    //const char str1 = conn("what", str[1]);
    //std::cout << conn("A", "B") << std::endl;
    const char *check = (std::string("what") + std::string(str[1])).c_str();
    std::cout << check << std::endl;
    std::pair<const char*, const char*> what = std::make_pair(check, str[0]);
    std::cout << what.first << " : " << what.second << std::endl;

    TT<2>::op();
    //TT()(1);
    //std::cout << TT<1>() << std::endl;
    TTT t;
    std::cout << t(2) << std::endl;

    TT<2> tt;
    std::cout << tt.size() << std::endl;

    const char *strlen0 = "\033[40;31mwhat\033[0m";
    const char *strlen1 = "\033[40;31m";
    const char *strlen2 = "\033[0m";
    std::cout << "\033[40;31mwhat\033[0m" << " : " << strlen(strlen2) << std::endl;

    const std::pair<const char*,const char*> pp = std::make_pair("ok", "null");
    const std::pair<const std::string, const std::string> ppp = pp;
    std::cout << ppp.first << " : " << ppp.second << std::endl;
    std::cout << std::string(ppp.first + str[1] + ppp.second) << std::endl;

    char str2[10] = "ok";
    temp1(str2);
    std::cout << strlen("") << std::endl;

    list("%d", 3);

    //ff f;
    //f.what();
    //std::cout << f << std::endl;
    //f<int> *fv = new fff<int>();
    //fv->what();
    //f<ff> *w = new ff();
    //w->what();
    //A *a = new AAA;
    //delete a;
    AAA a;
    //a.local.operator<< a;
    std::cout << a.output << std::endl;
    A *a1 = new AAA();
    delete a1;
    return 0;
}
