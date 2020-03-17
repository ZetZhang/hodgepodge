#ifndef __HDGD_DEBUG_H__
#define __HDGD_DEBUG_H__

//#include <sstream>
#include <string>
#include <string.h>

namespace hdgd
{

//template<typename T>
class Debug {
public:
    // XXX
    virtual std::string toString() const = 0;

    // FIXME
    //template<typename TT>
    //friend std::ostream& operator<<(std::ostream &os, const Debug<TT>&);

    virtual ~Debug() = default;
};

//template<typename T>
//std::ostream& operator<<(std::ostream &os, const Debug<T> &x) {
    //os << "\" " << x.toString() << "\" ";
    //return os;
//}

}

#endif
