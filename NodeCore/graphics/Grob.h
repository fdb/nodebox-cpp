#ifndef Grob_h
#define Grob_h

#include <iostream>
#include <ApplicationServices/ApplicationServices.h>

namespace NodeCore {

class Grob {
public:
    virtual ~Grob();
    virtual void _draw(CGContextRef ctx) = 0;

    virtual Grob* clone() const = 0;

    virtual bool operator==(const Grob& g) const = 0;
    virtual bool operator!=(const Grob& g) const = 0;
    friend std::ostream& operator<<(std::ostream& o, const Grob& bp);

};

} // namespace NodeCore

#endif // Grob_h
