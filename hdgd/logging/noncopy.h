#ifndef __NONCOPY_H__
#define __NONCOPY_H__

namespace hdgd
{

class NonCopy
{
public:
    NonCopy(const NonCopy &) = delete;
    NonCopy& operator=(const NonCopy &) = delete;
protected:
    NonCopy() = default;
    ~NonCopy() = default;
};

}

#endif
