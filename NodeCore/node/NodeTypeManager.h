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
