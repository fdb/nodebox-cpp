#ifndef NodeLibraryInterface_h
#define NodeLibraryInterface_h

#include <qstring>
#include "nodetype.h"

namespace NodeCore {

class NodeLibraryInterface
{
public:
    virtual ~NodeLibraryInterface() {}
    virtual QString name() const = 0;
    virtual QString description() const = 0;
    virtual QString version() const = 0;
    virtual QVector<NodeType*> nodeTypes() const = 0;
};

}

# endif // NodeLibraryInterface_h
