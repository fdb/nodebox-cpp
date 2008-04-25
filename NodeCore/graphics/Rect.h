#ifndef Rect_h
#define Rect_h

#include <ApplicationServices/ApplicationServices.h>

namespace NodeCore {

class Rect {
public:
    Rect();
    Rect(float x, float y, float width, float height);
    Rect(CGRect r);
    
    float getX() { return m_x; }
    float getY() { return m_y; }
    float getWidth() { return m_width; }
    float getHeight() { return m_height; }

    bool operator==(const Rect& r) const;
    bool operator!=(const Rect& r) const { return !operator==(r); }
    friend std::ostream& operator<<(std::ostream& o, const Rect& bp);
private:
    float m_x, m_y, m_width, m_height;
};

} // namespace NodeCore

#endif // Rect_h
