#ifndef __TEMP_H__
#define __TEMP_H__

#include <memory>

namespace hdgd
{

struct DefaultErr
{
    static void one() {  }
    static void two() {  }
};

template<typename I, class E = DefaultErr>
struct __output {
    I _value;
    typedef E _err;

    __output(const I &content) : _value(content) {}
    bool isOk() { return _value > I(0); }
    I result() { return _value; }
    I else_or(I inst) { return isOk() ? _value : inst; }
};

template<typename I, class E = DefaultErr>
class Steal
{
public:
    typedef __output<I, E> Output;

    Steal() : _output(std::make_shared<Output>(0)) {}

    Output& input(const I &&content) {
        _output->_value = content;
        return *_output;
    }

private:
    std::shared_ptr<Output> _output;
};

}


#endif
