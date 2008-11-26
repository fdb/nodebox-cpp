#ifndef Rect_h
#define Rect_h

#include <qrect.h>
#include <qdebug.h>

#include "point.h"

namespace NodeCore {

class Rect {
public:
    Rect();
    Rect(double x, double y, double width, double height);
    Rect(const Rect &r);
    Rect(const QRectF &r);
    
    bool isEmpty() const;

    double x() const;
    double y() const;
    double width() const;
    double height() const;
    
    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);
    
    void normalize();
    Rect normalized() const;
    
    void translate(const Point &p);
    void translate(double dx, double dy);
    Rect translated(const Point &p) const;
    Rect translated(double dx, double dy) const;
    
    void setRect(double x, double y, double width, double height);
    void getRect(double *x, double *y, double *width, double *height) const;
    
    bool contains(const Point &p) const;
    bool contains(double x, double y) const;
    bool contains(const Rect &r) const;
    void unite(const Rect &r);
    Rect united(const Rect &r) const;
    void intersect(const Rect &r);
    Rect intersected(const Rect &r) const;
    bool intersects(const Rect &r) const;
    
    Rect& operator=(const Rect& r);
    bool operator==(const Rect& r) const;
    bool operator!=(const Rect& r) const;

private:
    double m_x;
    double m_y;
    double m_width;
    double m_height;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const Rect &);
#endif

} // namespace NodeCore

#endif // Rect_h
