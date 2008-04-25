#ifndef BezierPath_h
#define BezierPath_h

#include <ApplicationServices/ApplicationServices.h>
#include <vector>

#include "graphics/Rect.h"
#include "graphics/Grob.h"
#include "graphics/PathElement.h"

namespace NodeCore {

class Transform;
class PathElement;

typedef std::vector<PathElement> PathElementList;
typedef PathElementList::iterator PathElementIterator;

class BezierPath : public Grob {
public:
    BezierPath();
    BezierPath(const BezierPath &path);
    virtual ~BezierPath();
    
    void moveto(float x, float y);
    void lineto(float x, float y);
    void curveto(float x1, float y1, float x2, float y2, float x3, float y3);
    void close();
    
    void rect(float x, float y, float width, float height);
    void oval(float x, float y, float width, float height);
    
    void clear();
    unsigned int size();
    bool isempty();
    NodeCore::Rect bounds();
    
    CGMutablePathRef cgPath();
    void transform(const Transform& transform);

    virtual void _draw(CGContextRef ctx);
    
    virtual BezierPath* clone() const;

    BezierPath& operator=(const BezierPath& bp);
    virtual bool operator==(const Grob& g) const;
    virtual bool operator!=(const Grob& g) const { return !operator==(g); }
    PathElement operator[](int n) const;
    friend std::ostream& operator<<(std::ostream& o, const BezierPath& bp);

private:
    PathElementList m_elements;
    CGMutablePathRef m_path; // transient
    bool m_dirty; // transient
};

} // namespace NodeCore

#endif // BezierPath_h
