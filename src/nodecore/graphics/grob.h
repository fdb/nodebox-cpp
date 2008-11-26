#ifndef Grob_h
#define Grob_h

#include <qdebug.h>
#include "rect.h"

namespace NodeCore {

class Grob {
public:
    virtual ~Grob() {}

    virtual Rect bounds() const = 0;

    virtual Grob* clone() const = 0;

    virtual bool operator==(const Grob& g) const = 0;
    virtual bool operator!=(const Grob& g) const = 0;
};

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug, const Grob &);
#endif

} // namespace NodeCore

#endif // Grob_h
