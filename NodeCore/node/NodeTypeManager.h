#ifndef NodeTypeManager_h
#define NodeTypeManager_h

#include "Node.h"

#include <string>
#include <map>
#include <iostream>

namespace NodeCore {

class Field;
class Node;

typedef Node* (*NodeInitializer)();
typedef std::map<std::string, NodeInitializer> NodeTypeMap;

class NodeTypeManager {
public:

    static void addNodeType(NodeType name, NodeInitializer initializer);
    
    static NodeInitializer getInitializer(const NodeType& name);
    static Node* initialize(const NodeType& name);
    
private:
    static NodeTypeMap getNodeTypeMap();
};


} // namespace NodeCore

#endif // NodeManager_h
