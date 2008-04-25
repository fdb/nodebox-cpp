#ifndef Point_h
#define Point_h

namespace NodeCore {

class PathElement;

class Point {
public:
    Point(float x=0, float y=0) : m_x(x), m_y(y) {}
    Point(const Point &point) : m_x(point.m_x), m_y(point.m_y) {}
    ~Point() {}
    
    float getX() { return m_x; }
    void setX(float x) { m_x = x; }
    float getY() { return m_y; }
    void setY(float y) { m_y = y; }
    
    Point& operator=(const Point& p);
    bool operator==(const Point& p) const;
    friend std::ostream& operator<<(std::ostream& o, const Point& p);
    friend std::ostream& operator<<(std::ostream& o, const PathElement& p);

    friend class PathElement;

private:
    float m_x;
    float m_y;
};

} // namespace NodeCore

#endif // Point_h
