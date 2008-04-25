/*
 * This file is part of NodeBox.
 *
 * Copyright (C) 2008 Frederik De Bleser (frederik@pandora.be)
 *
 * NodeBox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NodeBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NodeBox.  If not, see <http://www.gnu.org/licenses/>.
 */

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