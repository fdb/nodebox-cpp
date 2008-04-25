#ifndef Canvas_h
#define Canvas_h

#include <ApplicationServices/ApplicationServices.h>
#include <vector>

#include "graphics/Grob.h"
#include "graphics/BezierPath.h"

using std::vector;

namespace NodeCore {

typedef vector<Grob*> GrobList;
typedef vector<Grob*>::iterator GrobIterator;

class Canvas : public Grob {
public:
    Canvas(float width=DEFAULT_WIDTH, float height=DEFAULT_HEIGHT);
    Canvas(const Canvas &other);
    virtual ~Canvas();
    
    void append(const Grob& grob);
    unsigned int size() { return m_grobs.size(); };
    void clear() { m_grobs.clear(); };

    virtual void _draw(CGContextRef ctx);
    void save(std::string fname);

    virtual Canvas* clone() const;

    Canvas& operator=(const Canvas& c);    
    virtual bool operator==(const Grob& g) const;
    virtual bool operator!=(const Grob& g) const { return !operator==(g); }
    Grob* operator[](int n) const;
    friend std::ostream& operator<<(std::ostream& o, const Canvas& c);

private:
    void saveAsPDF(std::string fname);
    GrobList m_grobs;
    float m_width, m_height;
};

} // namespace NodeCore

#endif // Canvas_h
