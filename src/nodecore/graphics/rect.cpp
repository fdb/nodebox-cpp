#include "rect.h"
#include "qdebug.h"

namespace NodeCore {
    
double dmin(double d1, double d2)
{
    return (d1 < d2) ? d1 : d2;
}

double dmax(double d1, double d2)
{
    return (d1 > d2) ? d1 : d2;
}

Rect::Rect()
           : m_x(0), m_y(0), m_width(0), m_height(0)
{
}

Rect::Rect(double x, double y, double width, double height)
           : m_x(x), m_y(y), m_width(width), m_height(height)
{
}

Rect::Rect(const Rect &r)
           : m_x(r.m_x), m_y(r.m_y), m_width(r.m_width), m_height(r.m_height)
{
}

Rect::Rect(const QRectF &r)
           : m_x(r.x()), m_y(r.y()), m_width(r.width()), m_height(r.height())
{
}

bool Rect::isEmpty() const
{
    Rect n = normalized();
    return n.m_width <= 0 || n.m_height <= 0;
}

double Rect::x() const
{
    return m_x;
}

double Rect::y() const
{
    return m_y;
}

double Rect::width() const
{
    return m_width;
}

double Rect::height() const
{
    return m_height;
}

void Rect::setX(double x)
{
    m_x = x;
}


void Rect::setY(double y)
{
    m_y = y;
}

void Rect::setWidth(double width)
{
    m_width = width;
}

void Rect::setHeight(double height)
{
    m_height = height;
}

void Rect::normalize()
{
    if (m_width < 0) {
        m_x += m_width;
        m_width = -m_width;
    }
    if (m_height < 0) {
        m_y += m_height;
        m_height = -m_height;
    }
}

Rect Rect::normalized() const
{
    Rect r = *this;
    if (r.m_width < 0) {
        r.m_x += r.m_width;
        r.m_width = -r.m_width;
    }
    if (r.m_height < 0) {
        r.m_y += r.m_height;
        r.m_height = -r.m_height;
    }
    return r;
}

void Rect::translate(const Point &p)
{
    m_x += p.x();
    m_y += p.y();
}

void Rect::translate(double dx, double dy)
{
    m_x += dx;
    m_y += dy;
}

Rect Rect::translated(const Point &p) const
{
    return Rect(m_x + p.x(), m_y + p.y(), m_width, m_height);
}

Rect Rect::translated(double dx, double dy) const
{
    return Rect(m_x + dx, m_y + dy, m_width, m_height);
}

void Rect::setRect(double x, double y, double width, double height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}

void Rect::getRect(double *x, double *y, double *width, double *height) const
{
    *x = m_x;
    *y = m_y;
    *width = m_width;
    *height = m_height;
}

bool Rect::contains(const Point &p) const
{
    Rect r = normalized();
    return p.x() >= r.m_x && p.x() <= r.m_x + r.m_width &&
           p.y() >= r.m_y && p.y() <= r.m_y + r.m_height;
}

bool Rect::contains(const Rect &r) const
{
    Rect r1 = normalized();
    Rect r2 = r.normalized();
    return r2.m_x >= r1.m_x && r2.m_x + r2.m_width <= r1.m_x + r1.m_width &&
           r2.m_y >= r1.m_y && r2.m_y + r2.m_height <= r1.m_y + r1.m_height;
}

void Rect::unite(const Rect &r)
{
    Rect tmp = united(r);
    m_x = tmp.m_x;
    m_y = tmp.m_y;
    m_width = tmp.m_width;
    m_height = tmp.m_height;
}

Rect Rect::united(const Rect &r) const
{
    Rect r1 = normalized();
    Rect r2 = r.normalized();
    Rect u;
    u.m_x = dmin(r1.m_x, r2.m_x);
    u.m_y = dmin(r1.m_y, r2.m_y);
    u.m_width = dmax(r1.m_x + r1.m_width, r2.m_x + r2.m_width) - u.m_x;
    u.m_height = dmax(r1.m_y + r1.m_height, r2.m_y + r2.m_height) - u.m_y;
    return u;
}

void Rect::intersect(const Rect &r)
{
    Rect tmp = intersected(r);
    m_x = tmp.m_x;
    m_y = tmp.m_y;
    m_width = tmp.m_width;
    m_height = tmp.m_height;
}

Rect Rect::intersected(const Rect &r) const
{
    Rect r1 = normalized();
    Rect r2 = r.normalized();
    Rect i;
    i.m_x = dmax(r1.m_x, r2.m_x);
    i.m_y = dmax(r1.m_y, r2.m_y);
    i.m_width = dmin(r1.m_width, r2.m_width);
    i.m_height = dmin(r1.m_height, r2.m_height);
    return i.isEmpty() ? Rect() : i;
}

bool Rect::intersects(const Rect &r) const
{
    Rect r1 = normalized();
    Rect r2 = r.normalized();
    return dmax(r1.m_x, r2.m_x) < dmin(r1.m_x + r1.m_width, r2.m_x + r2.m_width) &&
           dmax(r1.m_y, r2.m_y) < dmin(r1.m_y + r1.m_height, r2.m_y + r2.m_height);
}

Rect& Rect::operator=(const Rect &r)
{
    if (this == &r) return *this;
    m_x = r.m_x;
    m_y = r.m_y;
    m_width = r.m_width;
    m_height = r.m_height;
    return *this;
}

bool Rect::operator==(const Rect &r) const
{
    return m_x == r.m_x
        && m_y == r.m_y
        && m_width == r.m_width
        && m_height == r.m_height;
}


bool Rect::operator!=(const Rect &r) const
{
    return m_x != r.m_x
        || m_y != r.m_y
        || m_width != r.m_width
        || m_height != r.m_height;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const Rect &r)
{
    d.nospace() << "Rect(" << r.x() << ", " << r.y()
                << ", " << r.width() << ", " << r.height() << ")";
    return d;
}
#endif

} // namespace NodeCore
