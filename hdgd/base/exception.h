#ifndef __HDGD_EXCEPTION_H__
#define __HDGD_EXCEPTION_H__

#include <exception>

namespace hdgd
{

class Exception : public std::exception
{
public:
    //const char* what() const throw();
    const char* what() const noexcept override {
        return _message.c_str();
    }

    const char* stackTrace() const noexcept {
        return "";
    }

private:
    std::string _message;
};

}

#endif
