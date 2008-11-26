#ifndef Color_h
#define Color_h

#include <qcolor.h>
#include <qdebug.h>

namespace NodeCore {

class Color
{

public:
    Color(double r, double g, double b, double a = 1.0);
    Color(const QString &name);
    Color(const Color &color);
    Color(const QColor &color);

    QColor qColor() const;
    
    double red() const;
    double green() const;
    double blue() const;
    double alpha() const;
    void setRed(double red);
    void setGreen(double green);
    void setBlue(double blue);
    void setAlpha(double alpha);
    
    double cyan() const;
    double magenta() const;
    double yellow() const;
    double black() const;
    void setCyan(double cyan);
    void setMagenta(double magenta);
    void setYellow(double yellow);
    void setBlack(double black);
    
    double hue() const;
    double saturation() const;
    double brightness() const;
    void setHue(double hue);
    void setSaturation(double saturation);
    void setBrightness(double brightness);
    
    Color lighter(double factor) const;
    Color darker(double factor) const;
    
    static Color fromRgb(double r, double g, double b, double a = 1.0);
    static Color fromHsv(double h, double s, double v, double a = 1.0);
    static Color fromCmyk(double c, double m, double y, double k, double a = 1.0);

    Color &operator=(const Color &c);
    bool operator==(const Color &c) const;
    bool operator!=(const Color &c) const;

private:
    QColor *m_color;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const Color &c);
#endif

} // namespace NodeCore

#endif // Color_h
