#include "grob.h"

namespace NodeCore {

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug d, const Grob &) {
    d.nospace() << "Grob()";
    return d.space();
}
#endif

} // namespace NodeCore
