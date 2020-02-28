#include <iostream>
#include <memory>
#include <string>
#include "temp.h"

namespace hdgd
{
template<typename I>
struct Some
{
    typedef Steal<I> Stealv;
    typedef typename Stealv::Output output;
    Stealv _steal;

    Some() : _steal() {}
    ~Some() {}
    output operate(const I &&v) {
        return _steal.input(std::move(v));
    }
};
}

int main(int argc, const char *argv[])
{
    // option: some | none
    // result: Ok | Err
    // panic
    // Abort
    hdgd::Some<int32_t> s;
    s.operate(1).isOk();
    s.operate(0).result();
    s.operate(-1).else_or(130);

    typedef hdgd::Steal<int> Stealv;
    typedef typename Stealv::Output output;
    std::shared_ptr<Stealv> ste = std::make_shared<Stealv>();
    std::cout << ste->input(1).isOk() << std::endl;
    std::cout << ste->input(0).result() << std::endl;
    std::cout << ste->input(-1).else_or(130) << std::endl;

    std::shared_ptr<hdgd::Some<float>> ste1 = std::make_shared<hdgd::Some<float>>();
    std::cout << ste1->operate(3.13).isOk() << std::endl;
    std::cout << ste1->operate(3.13).result() << std::endl;
    return 0;
}
