#include "pathelement.h"
#include "qdebug.h"

namespace NodeCore {

PathElement::PathElement(const PathCommand &cmd)
           : m_command(cmd)
{
}

PathElement::PathElement(const PathCommand &cmd, Point &p)
           : m_command(cmd), m_point(p)
{
}

PathElement::PathElement(const PathCommand &cmd, double x, double y)
           : m_command(cmd), m_point(Point(x, y))
{
}

PathElement::PathElement(const PathCommand &cmd, Point &p1, Point &p2, Point &p3)
           : m_command(cmd), m_point(p3), m_control1(p1), m_control2(p2)
{
}

PathElement::PathElement(const PathCommand &cmd, double x1, double y1, double x2, double y2, double x3, double y3)
           : m_command(cmd), m_point(Point(x3, y3)), m_control1(Point(x1, y1)), m_control2(Point(x2, y2))
{
}

PathElement::PathElement(const PathElement &pe)
           : m_command(pe.m_command), m_point(pe.m_point), m_control1(pe.m_control1), m_control2(pe.m_control2)
{
}

PathElement::~PathElement()
{
}

PathElement::PathCommand PathElement::command() const
{
    return m_command;
}

double PathElement::x() const
{
    return m_point.x();
}

double PathElement::y() const
{
    return m_point.y();
}

Point PathElement::point() const
{
    return m_point;
}

Point PathElement::control1() const
{
    return m_control1;
}

Point PathElement::control2() const
{
    return m_control2;
}

bool PathElement::operator==(const PathElement& pe) const
{
    return m_command == pe.m_command
        && m_point == pe.m_point
        && m_control1 == pe.m_control1
        && m_control2 == pe.m_control2;
}

bool PathElement::operator!=(const PathElement& pe) const
{
    return m_command != pe.m_command
        || m_point != pe.m_point
        || m_control1 != pe.m_control1
        || m_control2 != pe.m_control2;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const PathElement &pe)
{
    switch (pe.command()) {
        case PathElement::MoveToCommand:
            d.nospace() << "PathElement(MoveToCommand, " << pe.point().x() << ", " << pe.point().y() << ")"; break;
        case PathElement::LineToCommand:
            d.nospace() << "PathElement(LineToCommand, " << pe.point().x() << ", " << pe.point().y() << ")"; break;
        case PathElement::CurveToCommand:
            d.nospace() << "PathElement(CurveToCommand, " << pe.control1().x() << ", " << pe.control1().y() << ", "
                                                          << pe.control2().x() << ", " << pe.control2().y() << ", "
                                                          << pe.point().x() << ", " << pe.point().y() << ")"; break;
        case PathElement::CloseCommand:
            d.nospace() << "PathElement(CloseCommand)"; break;
        default:
            assert(false);
    }
    return d;
}
#endif

} // namespace NodeCore
