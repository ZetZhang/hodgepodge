#ifndef __COMPARABLE_H__
#define __COMPARABLE_H__

namespace hdgd
{

template<typename T>
class Comparable
{
public:
    // friend elif
    virtual bool operator==(const T &rhs) const = 0;
    virtual bool operator!=(const T &rhs) const = 0;
    virtual bool operator<(const T &rhs) const = 0;
    virtual bool operator<=(const T &rhs) const = 0;
    virtual bool operator>(const T &rhs) const = 0;
    virtual bool operator>=(const T &rhs) const = 0;

    virtual ~Comparable() = default;
};

}

#endif
