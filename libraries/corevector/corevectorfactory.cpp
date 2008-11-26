#include "corevectorfactory.h"
#include "rectnode.h"

namespace CoreVector {

Node *CoreVectorFactory::createNode(const NodeType *t) const
{
    QString name = t->name();
    if (name == "rect") {
        //return new RectNode(t);
    }
    return NULL;
}

} // namespace CoreVector
