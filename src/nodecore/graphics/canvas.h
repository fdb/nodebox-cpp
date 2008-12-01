#ifndef Canvas_h
#define Canvas_h

#include <qdebug.h>

#include "color.h"
#include "group.h"

namespace NodeCore {

class Canvas : public Group
{
public:
    Canvas();
    Canvas(const Color& background);
    Canvas(const Canvas &canvas);
    virtual ~Canvas();
    
    double width() const;
    double height() const;
    void setWidth(double width);
    void setHeight(double height);
    
    Color background() const;
    void background(const Color& color);

    virtual void draw(QPainter& p) const;

private:
    double m_width;
    double m_height;
    Color m_background;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const Canvas &c);
#endif

} // namespace NodeCore

#endif // Canvas_h
