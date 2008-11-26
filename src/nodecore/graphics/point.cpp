#include "point.h"
#include "qdebug.h"

namespace NodeCore {
    
Point::Point()
     : m_x(0), m_y(0)
{
}

Point::Point(double x, double y)
     : m_x(x), m_y(y)
{
}

Point::Point(const Point &p)
            : m_x(p.m_x), m_y(p.m_y)
{
}

Point::Point(const QPointF &p)
            : m_x(p.x()), m_y(p.y())
{
}

QPointF Point::qPointF() const
{
    return QPointF(m_x, m_y);
}

double Point::x() const
{
    return m_x;
}

double Point::y() const
{
    return m_y;
}

void Point::setX(double x)
{
    m_x = x;
}


void Point::setY(double y)
{
    m_y = y;
}

Point &Point::operator+=(const Point &p)
{
    m_x += p.m_x;
    m_y += p.m_y;
    return *this;
}

Point &Point::operator-=(const Point &p)
{
    m_x -= p.m_x;
    m_y -= p.m_y;
    return *this;
}

Point &Point::operator*=(double c)
{
    m_x *= c;
    m_y *= c;
    return *this;
}

Point &Point::operator/=(double c)
{
    m_x /= c;
    m_y /= c;
    return *this;
}

bool Point::operator==(const Point &p) const
{
    return m_x == p.m_x
        && m_y == p.m_y;
}

bool Point::operator!=(const Point &p) const
{
    return m_x != p.m_x
        || m_y != p.m_y;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const Point &p)
{
    d.nospace() << "Point(" << p.x() << ", " << p.y() << ")";
    return d;
}
#endif

} // namespace NodeCore
