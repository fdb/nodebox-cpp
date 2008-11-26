#ifndef NodeFactoryInterface_h
#define NodeFactoryInterface_h

#include <QtPlugin>
#include "nodetype.h"

namespace NodeCore {

// small mapping from node type name to node instance

class NodeFactoryInterface
{
    Node *createNode(const NodeType *t);
};

}

Q_DECLARE_INTERFACE(NodeCore::NodeFactoryInterface,
                    "net.nodebox.NodeFactoryInterface/1.0")

#endif // NodeFactoryInterface_h
