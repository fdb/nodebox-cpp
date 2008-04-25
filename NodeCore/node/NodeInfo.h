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

#ifndef NodeInfo_h
#define NodeInfo_h

#include "Node.h"

namespace NodeCore {

class NodeLibrary;

typedef std::string NodeName;

typedef Node* (*NodeCreator)();

enum NodeLibraryType {
    kUnknown = 0,
    kNative,
    kPython,
    kUnsupported
};

typedef std::string NodeLibraryName;

class NodeCreationError : public std::exception
{
public:
    NodeCreationError(NodeLibraryName libraryName, NodeName nodeName, std::string msg="")
            : m_libraryName(libraryName), m_nodeName(nodeName), m_msg(msg) {}
    virtual ~NodeCreationError() throw() {}
    NodeLibraryName m_libraryName;
    NodeName m_nodeName;
    std::string m_msg;
};

class NodeInfo
{
public:
    NodeInfo(NodeLibrary& library, NodeName name, void* data);
    ~NodeInfo();
    
    NodeLibrary& getLibrary();
    NodeName getName();
    Node* create();

private:
    Node* createNativeNode();
    Node* createPythonNode();

    NodeLibrary& m_library;
    NodeName m_name;
    void* m_data;
};

} // namespace NodeCore

#endif // NodeInfo_h