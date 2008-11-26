#ifndef PathElement_h
#define PathElement_h

#include <qdebug.h>
#include <qpainterpath.h>

#include "point.h"

namespace NodeCore {

class PathElement
{
public:
    
    enum PathCommand {
        MoveToCommand,
        LineToCommand,
        CurveToCommand,
        CloseCommand
    };
    
    PathElement(const PathCommand &cmd);
    PathElement(const PathCommand &cmd, Point &p);
    PathElement(const PathCommand &cmd, double x, double y);
    PathElement(const PathCommand &cmd, Point &p1, Point &p2, Point &p3);
    PathElement(const PathCommand &cmd, double x1, double y1, double x2, double y2, double x3, double y3);
    PathElement(const PathElement &pe);
    virtual ~PathElement();

    PathCommand command() const;
    double x() const;
    double y() const;
    Point point() const;
    Point control1() const;
    Point control2() const;

    virtual bool operator==(const PathElement &pe) const;
    virtual bool operator!=(const PathElement &pe) const;
    
private:
    PathCommand m_command;
    Point m_point;
    Point m_control1;
    Point m_control2;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const PathElement &pe);
#endif

} // namespace NodeCore

#endif // PathElement_h
