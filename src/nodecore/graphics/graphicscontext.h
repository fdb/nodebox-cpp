#ifndef GraphicsContext_h
#define GraphicsContext_h

#include <qdebug.h>
#include <qobject.h>

#include "canvas.h"

namespace NodeCore {

class GraphicsContext : public QObject
{
    Q_OBJECT
public:
    GraphicsContext();
    virtual ~GraphicsContext();
    
    Canvas *canvas() const;

public slots:
    BezierPath *rect(double x, double y, double width, double height, bool draw = true);
    
private:
    Canvas *m_canvas;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const GraphicsContext &);
#endif

} // namespace NodeCore

#endif // GraphicsContext_h
