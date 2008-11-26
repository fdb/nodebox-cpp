#include "bezierpath.h"
#include "point.h"
#include "rect.h"
#include "transform.h"

namespace NodeCore {
    
Transform::Transform()
         : m_transform(new QTransform())
{
}

Transform::Transform(const Transform &t)
         : m_transform(new QTransform(*t.m_transform))
{
}

Transform::Transform(const QTransform &t)
         : m_transform(new QTransform(t))
{
}


Transform Transform::inverted() const
{
    return Transform(m_transform->inverted());
}

void Transform::translate(const Point &p)
{
    m_transform->translate(p.x(), p.y());
}

void Transform::translate(double x, double y)
{
    m_transform->translate(x, y);
}

void Transform::scale(double sx, double sy)
{
    m_transform->scale(sx, sy);
}

void Transform::rotate(double angle)
{
    m_transform->rotate(angle);
}

void Transform::rotateRadians(double angle)
{
    m_transform->rotateRadians(angle);
}

void Transform::shear(double sh, double sv)
{
    m_transform->shear(sh, sv);
}


Point Transform::map(const Point &p) const
{
    return Point(m_transform->map(p.qPointF()));
}

Rect Transform::map(const Rect &r) const
{
    return Rect(m_transform->mapRect(r.qRectF()));
}

BezierPath Transform::map(const BezierPath &p) const
{
    return BezierPath(m_transform->map(p.qPainterPath()));
}

bool Transform::operator==(const Transform &t) const
{
    return m_transform == t.m_transform;
}

bool Transform::operator!=(const Transform &t) const
{
    return m_transform != t.m_transform;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const Transform &t)
{
    d.nospace() << "Transform()";
    return d;
}
#endif

} // namespace NodeCore
