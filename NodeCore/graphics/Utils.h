#ifndef Utils_h
#define Utils_h

#include <cmath>

namespace NodeCore {

inline float radians(float degrees)
{
    return degrees * M_PI / 180.0;
}

inline float degrees(float radians)
{
    return radians * 180.0 / M_PI;
}

}

#endif // Utils_h