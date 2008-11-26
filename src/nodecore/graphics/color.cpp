#include "color.h"

namespace NodeCore {
    
Color::Color(double r, double g, double b, double a)
    : m_color(NULL)
{
    m_color = new QColor(QColor::fromRgbF(r, g, b, a));
}

Color::Color(const QString &name)
     : m_color(new QColor(name))
{
}

Color::Color(const Color &color)
     : m_color(new QColor(*color.m_color))
{
}

Color::Color(const QColor &color)
     : m_color(new QColor(color))
{
}

double Color::red() const
{
    return m_color->redF();
}

double Color::green() const
{
    return m_color->greenF();
}

double Color::blue() const
{
    return m_color->blueF();
}

double Color::alpha() const
{
    return m_color->alphaF();
}

void Color::setRed(double red)
{
    m_color->setRedF(red);
}

void Color::setGreen(double green)
{
    m_color->setGreenF(green);
}

void Color::setBlue(double blue)
{
    m_color->setBlueF(blue);
}

void Color::setAlpha(double alpha)
{
    m_color->setAlphaF(alpha);
}

double Color::cyan() const
{
    return m_color->cyanF();
}

double Color::magenta() const
{
    return m_color->magentaF();
}

double Color::yellow() const
{
    return m_color->yellowF();
}

double Color::black() const
{
    return m_color->blackF();
}

void Color::setCyan(double cyan)
{
    m_color->setCmykF(cyan, magenta(), yellow(), black(), alpha());
}

void Color::setMagenta(double magenta)
{
    m_color->setCmykF(cyan(), magenta, yellow(), black(), alpha());
}

void Color::setYellow(double yellow)
{
    m_color->setCmykF(cyan(), magenta(), yellow, black(), alpha());
}

void Color::setBlack(double black)
{
    m_color->setCmykF(cyan(), magenta(), yellow(), black, alpha());
}

double Color::hue() const
{
    // Qt stores hueF from 0.0 - 360.0; we return from 0.0 to 1.0.
    return m_color->hueF() / 360.0;
}

double Color::saturation() const
{
    return m_color->saturationF();
}

double Color::brightness() const
{
    return m_color->valueF();
}

void Color::setHue(double hue)
{
    // Qt stores hueF from 0.0 - 360.0; we return from 0.0 to 1.0.
    m_color->setHsvF(hue * 360.0, saturation(), brightness(), alpha());
}

void Color::setSaturation(double saturation)
{
    m_color->setHsvF(hue() * 360.0, saturation, brightness(), alpha());
}

void Color::setBrightness(double brightness)
{
    m_color->setHsvF(hue() * 360.0, saturation(), brightness, alpha());
}

Color Color::lighter(double factor) const
{
    // TODO: implement
    return *this;
}

Color Color::darker(double factor) const
{
    // TODO: implement
    return *this;
}

Color Color::fromRgb(double r, double g, double b, double a)
{
    return Color(QColor::fromRgbF(r, g, b, a));
}

Color Color::fromHsv(double h, double s, double v, double a)
{
    return Color(QColor::fromHsvF(h * 360.0, s, v, a));
}

Color Color::fromCmyk(double c, double m, double y, double k, double a)
{
    return Color(QColor::fromCmykF(c, m, y, k, a));
}

Color &Color::operator=(const Color &c)
{
    m_color = c.m_color;
    return *this;
}

bool Color::operator==(const Color &c) const
{
    return m_color == c.m_color;
}

bool Color::operator!=(const Color &c) const
{
    return m_color != c.m_color;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const Color &c) {
    d.nospace() << "Color(" << c.red() << ", " << c.green() << ", "
                            << c.blue() << ", "  << c.alpha() << ")";
    return d.space();
}
#endif

} // namespace NodeCore
