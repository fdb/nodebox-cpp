#ifndef Transform_h
#define Transform_h

#include <qdebug.h>
#include <qtransform.h>

namespace NodeCore {

class Point;
class Rect;
class BezierPath;

class Transform
{
public:

    Transform();
    Transform(const Transform &t);
    Transform(const QTransform &t);
    
    Transform inverted() const;
    
    void translate(const Point &p);
    void translate(double x, double y);
    void scale(double sx, double sy);
    void rotate(double angle);
    void rotateRadians(double angle);
    void shear(double sh, double sv);
    
    Point map(const Point &p) const;
    Rect map(const Rect &p) const;
    BezierPath map(const BezierPath &p) const;
    
    bool operator==(const Transform &t) const;
    bool operator!=(const Transform &t) const;
    
private:
    QTransform *m_transform;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const Transform &t);
#endif

} // namespace NodeCore

#endif // Transform_h
