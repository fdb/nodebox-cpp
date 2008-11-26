#ifndef BezierPath_h
#define BezierPath_h

#include <qdebug.h>
#include <qpainterpath.h>

#include "color.h"
#include "grob.h"
#include "pathelement.h"
#include "rect.h"

namespace NodeCore {

class BezierPath : public Grob
{
public:
    BezierPath();
    BezierPath(const BezierPath &path);
    BezierPath(const QPainterPath &path);
    virtual ~BezierPath();

    QPainterPath qPainterPath() const;
    
    void moveTo(const Point &p);
    void moveTo(double x, double y);
    void lineTo(const Point &p);
    void lineTo(double x, double y);
    void curveTo(const Point &p1, const Point &p2, const Point &p3);
    void curveTo(double x1, double y1, double x2, double y2, double x2, double y3);
    void close();
    
    void addRect(const Rect &r);
    void addRect(double x, double y, double width, double height);
    void addRoundedRect(const Rect &r, double rx, double ry);
    void addRoundedRect(double x, double y, double width, double height, double rx, double ry);
    void addEllipse(const Rect &r);
    void addEllipse(double x, double y, double width, double height);
    void addLine(const Point &p1, const Point &p2);
    void addLine(double x1, double y1, double x2, double y2);

    bool contains(const Point &p);
    bool contains(const Rect &r);
    bool contains(const BezierPath &p);
    bool intersects(const Rect &r);
    bool intersects(const BezierPath &p);
    BezierPath intersected(const BezierPath &p);
    BezierPath subtracted(const BezierPath &p);
    BezierPath united(const BezierPath &p);

    virtual Rect bounds() const;

    virtual Grob* clone() const;

    virtual bool operator==(const Grob& g) const;
    virtual bool operator!=(const Grob& g) const;
    
private:
    QPainterPath *m_path;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const BezierPath &);
#endif

} // namespace NodeCore

#endif // BezierPath_h
