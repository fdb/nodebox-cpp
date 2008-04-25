#include <iostream>
#include <ApplicationServices/ApplicationServices.h>

#include "NodeCore.h"

namespace NodeCore {

Rect::Rect()
    : m_x(0),
      m_y(0),
      m_width(0),
      m_height(0)
{
}

Rect::Rect(float x, float y, float width, float height)
    : m_x(x),
      m_y(y),
      m_width(width),
      m_height(height)
{
}

Rect::Rect(CGRect r)
{
    m_x = r.origin.x;
    m_y = r.origin.y;
    m_width = r.size.width;
    m_height = r.size.height;
}

bool Rect::operator==(const Rect& r) const
{
    return m_x == r.m_x
        && m_y == r.m_y
        && m_width == r.m_width
        && m_height == r.m_height;
}

std::ostream& operator<<(std::ostream& o, const Rect& r)
{
    o << "Rect(" << r.m_x << ", " << r.m_y << ", " << r.m_width << ", " << r.m_height << ")";
    return o;
}

} // namespace NodeCore