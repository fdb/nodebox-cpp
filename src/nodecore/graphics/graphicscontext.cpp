#include "bezierpath.h"
#include "canvas.h"
#include "graphicscontext.h"
#include "point.h"
#include "rect.h"
#include "transform.h"

namespace NodeCore {

GraphicsContext::GraphicsContext()
               : m_canvas(new Canvas())
{
}

GraphicsContext::~GraphicsContext()
{
    delete m_canvas;
}

Canvas *GraphicsContext::canvas() const
{
    return m_canvas;
}

BezierPath *GraphicsContext::rect(double x, double y, double width, double height, bool draw)
{
    BezierPath *p = new BezierPath();
    p->addRect(x, y, width, height);
    if (draw)
        m_canvas->append(p);
    return p;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const GraphicsContext &)
{
    d.nospace() << "GraphicsContext()";
    return d;
}
#endif

} // namespace NodeCore
