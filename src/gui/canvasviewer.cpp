#include "canvasviewer.h"

CanvasViewer::CanvasViewer(QWidget *parent)
            : QWidget(parent), m_canvas(NULL)
{
}

CanvasViewer::CanvasViewer(Canvas *canvas, QWidget *parent)
            : QWidget(parent), m_canvas(canvas)
{
}

Canvas *CanvasViewer::canvas() const
{
    return m_canvas;
}

void CanvasViewer::setCanvas(Canvas *canvas)
{
    m_canvas = canvas;
    update();
}

void CanvasViewer::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    if (m_canvas != NULL)
        m_canvas->draw(p);
}
