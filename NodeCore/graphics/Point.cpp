#include "config.h"
#include "Point.h"

namespace NodeCore {

Point& Point::operator=(const Point& p)
{
    if (this == &p) return *this;
    m_x = p.m_x;
    m_y = p.m_y;
    return *this;
}

bool Point::operator==(const Point& p) const
{
    return m_x == p.m_x 
        && m_y == p.m_y;
}

std::ostream& operator<<(std::ostream& o, const Point& p)
{
    return o << "[" << p.m_x << "," << p.m_y << "]";
}

} // namespace NodeCore