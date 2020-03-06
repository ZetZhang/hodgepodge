#ifndef __NONCOPY_H__
#define __NONCOPY_H__

namespace hdgd
{

class NonCopyable
{
public:
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable& operator=(const NonCopyable &) = delete;
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

}

#endif
