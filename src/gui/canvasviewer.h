#ifndef CanvasViewer_h
#define CanvasViewer_h

#include <qwidget.h>

#include "canvas.h"

using namespace NodeCore;

class CanvasViewer : public QWidget
{
    Q_OBJECT
public:
    CanvasViewer(QWidget *parent = 0);
    CanvasViewer(Canvas *canvas, QWidget *parent = 0);

    Canvas *canvas() const;
    void setCanvas(Canvas *canvas);

private:
    Canvas *m_canvas;
};

#endif // CanvasViewer_h
