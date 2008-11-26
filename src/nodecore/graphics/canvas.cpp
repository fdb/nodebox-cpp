#include "canvas.h"

namespace NodeCore {
    
Canvas::Canvas()
      : Group(), m_width(1000), m_height(1000), m_background(Color(1, 1, 1))
{
}

Canvas::Canvas(const Color& background)
      : Group(), m_width(1000), m_height(1000), m_background(background)
{
}

Canvas::Canvas(const Canvas &canvas)
      : Group(canvas), m_width(canvas.m_width), m_height(canvas.m_height), m_background(canvas.m_background)
{
}

Canvas::~Canvas()
{
}

double Canvas::width() const
{
    return m_width;
}

double Canvas::height() const
{
    return m_height;
}

void Canvas::setWidth(double width)
{
    m_width = width;
}

void Canvas::setHeight(double height)
{
    m_height = height;
}

Color Canvas::background() const
{
    return m_background;
}

void Canvas::background(const Color& color)
{
    m_background = color;
}

} // namespace NodeCore
