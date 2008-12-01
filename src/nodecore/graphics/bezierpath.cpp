#include <qpoint.h>

#include "bezierpath.h"

namespace NodeCore {
    
BezierPath::BezierPath()
          : Grob(),
            m_path(new QPainterPath()),
            m_fill(Color()),
            m_stroke(Color::invisibleColor())
{
}

BezierPath::BezierPath(const BezierPath &path)
          : Grob(),
            m_path(new QPainterPath(*path.m_path)),
            m_fill(Color()),
            m_stroke(Color::invisibleColor())
{
}

BezierPath::BezierPath(const QPainterPath &path)
          : Grob(),
            m_path(new QPainterPath(path)),
            m_fill(Color()),
            m_stroke(Color::invisibleColor())
{
}

BezierPath::~BezierPath()
{
    delete m_path;
}

QPainterPath BezierPath::qPainterPath() const
{
    return QPainterPath(*m_path);
}

void BezierPath::moveTo(const Point &p)
{
    m_path->moveTo(p.x(), p.y());
}

void BezierPath::moveTo(double x, double y)
{
    m_path->moveTo(x, y);
}

void BezierPath::lineTo(const Point &p)
{
    m_path->lineTo(p.x(), p.y());
}

void BezierPath::lineTo(double x, double y)
{
    m_path->lineTo(x, y);
}

void BezierPath::curveTo(const Point &p1, const Point &p2, const Point &p3)
{
    m_path->cubicTo(p1.x(), p1.y(), p2.x(), p2.y(), p3.x(), p3.y());
}

void BezierPath::curveTo(double x1, double y1, double x2, double y2, double x3, double y3)
{
    m_path->cubicTo(x1, y1, x2, y2, x3, y3);
}

void BezierPath::close()
{
    m_path->closeSubpath();
}

void BezierPath::addRect(const Rect &r)
{
    m_path->addRect(r.x(), r.y(), r.width(), r.height());
}

void BezierPath::addRect(double x, double y, double width, double height)
{
    m_path->addRect(x, y, width, height);
}

void BezierPath::addRoundedRect(const Rect &r, double rx, double ry)
{
    m_path->addRoundedRect(r.x(), r.y(), r.width(), r.height(), rx, ry);
}

void BezierPath::addRoundedRect(double x, double y, double width, double height, double rx, double ry)
{
    m_path->addRoundedRect(x, y, width, height, rx, ry);
}

void BezierPath::addEllipse(const Rect &r)
{
    m_path->addEllipse(r.x(), r.y(), r.width(), r.height());
}

void BezierPath::addEllipse(double x, double y, double width, double height)
{
    m_path->addEllipse(x, y, width, height);
}

void BezierPath::addLine(const Point &p1, const Point &p2)
{
    m_path->moveTo(p1.x(), p1.y());
    m_path->lineTo(p2.x(), p2.y());
}

void BezierPath::addLine(double x1, double y1, double x2, double y2)
{
    m_path->moveTo(x1, y1);
    m_path->lineTo(x2, y2);
}


bool BezierPath::contains(const Point &p)
{
    return m_path->contains(QPointF(p.x(), p.y()));
}

bool BezierPath::contains(const Rect &r)
{
    return m_path->contains(QRectF(r.x(), r.y(), r.width(), r.height()));
}

bool BezierPath::contains(const BezierPath &p)
{
    return m_path->contains(*p.m_path);
}

bool BezierPath::intersects(const Rect &r)
{
    return m_path->intersects(QRectF(r.x(), r.y(), r.width(), r.height()));
}

bool BezierPath::intersects(const BezierPath &p)
{
    return m_path->intersects(*p.m_path);
}

BezierPath BezierPath::intersected(const BezierPath &p)
{
    return BezierPath(m_path->intersected(*p.m_path));
}

BezierPath BezierPath::subtracted(const BezierPath &p)
{
    return BezierPath(m_path->subtracted(*p.m_path));
}

BezierPath BezierPath::united(const BezierPath &p)
{
    return BezierPath(m_path->united(*p.m_path));
}

Rect BezierPath::bounds() const
{
    return Rect(m_path->boundingRect());
}

void BezierPath::draw(QPainter &p) const
{
    const QPainterPath &constPath = (const QPainterPath&)*m_path;
    if (!m_fill.isInvisible()) {
        p.fillPath(constPath, m_fill.qBrush());
    }
    if (!m_stroke.isInvisible()) {
        p.strokePath(constPath, m_stroke.qPen(m_strokeWidth));
    }
}

Grob* BezierPath::clone() const
{
    return new BezierPath(*this);
}

bool BezierPath::operator==(const Grob &g) const
{
    return false;
}

bool BezierPath::operator!=(const Grob &g) const
{
    return false;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const BezierPath &p) {
    d.nospace() << "BezierPath()";
    return d.space();
}
#endif

} // namespace NodeCore
