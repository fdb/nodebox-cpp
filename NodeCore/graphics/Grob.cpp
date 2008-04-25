#include "config.h"
#include "Grob.h"

namespace NodeCore {

Grob::~Grob()
{
}

std::ostream& operator<<(std::ostream& o, const Grob& bp)
{
    o << "Grob()";
    return o;
}

} // namespace NodeCore