#ifndef Point_h
#define Point_h

#include <qpoint.h>

namespace NodeCore {

class Rect;

class Point
{
public:
    Point();
    Point(double x, double y);
    Point(const Point &p);
    Point(const QPointF &p);
    
    double x() const;
    double y() const;
    void setX(double x);
    void setY(double y);
    
    Point &operator+=(const Point &p);
    Point &operator-=(const Point &p);
    Point &operator*=(double c);
    Point &operator/=(double c);
    
    bool operator==(const Point &p) const;
    bool operator!=(const Point &p) const;

private:
    double m_x;
    double m_y;
};

} // namespace NodeCore

#endif // Point_h
