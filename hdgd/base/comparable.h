#ifndef __HDGD_COMPARABLE_H__
#define __HDGD_COMPARABLE_H__

namespace hdgd
{

template<typename T>
class Comparable
{
public:
    // 为了防止隐式转换，构造函数将是explicit，否则不必继承接口直接创建non-member non-friend operation functions
    // FIXME：需考虑继承纯虚函数接口是否必要
    virtual bool operator==(const T &rhs) const = 0;
    virtual bool operator!=(const T &rhs) const = 0;
    virtual bool operator<(const T &rhs) const = 0;
    virtual bool operator<=(const T &rhs) const = 0;
    virtual bool operator>(const T &rhs) const = 0;
    virtual bool operator>=(const T &rhs) const = 0;

    virtual ~Comparable() noexcept = default;
};

}

#endif
