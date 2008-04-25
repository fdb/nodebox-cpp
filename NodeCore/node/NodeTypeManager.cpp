#include "NodeCore.h"

namespace NodeCore {

void NodeTypeManager::addNodeType(NodeType name, NodeInitializer initializer)
{ 
    getNodeTypeMap()[name] = initializer;
}

NodeInitializer NodeTypeManager::getInitializer(const NodeType& name) {
    NodeTypeMap ntm = getNodeTypeMap();
    if (ntm.empty()) {
        std::cout << "Initializing the basics." << std::endl;
    }
    return ntm[name];
}

Node* NodeTypeManager::initialize(const NodeType& name) {
    NodeInitializer init; //  = getInitializer(type);    
    // TODO: Use the map. The map always remains at size 0 -- why?
    Node* n = (*init)();
    return n;
}
    
NodeTypeMap NodeTypeManager::getNodeTypeMap() {
    static NodeTypeMap m_typeMap = NodeTypeMap();
    return m_typeMap;
}

} // namespace NodeCore