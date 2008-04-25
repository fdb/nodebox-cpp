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

#include <iostream>
#include <Python/Python.h>

#include "NodeCore.h"

namespace NodeCore {

NodeInfo::NodeInfo(NodeLibrary& library, NodeName name, void* data)
    : m_library(library), m_name(name), m_data(data) {}

NodeInfo::~NodeInfo()
{
    switch (m_library.getType()) {
        case kNative:
            break;
        case kPython:
            Py_XDECREF((PyObject*)m_data);
            break;
    }
}

NodeLibrary& NodeInfo::getLibrary() { return m_library; }

NodeName NodeInfo::getName() { return m_name; }

Node* NodeInfo::create() {
    switch (m_library.getType()) {
        case kNative:
            return createNativeNode();
        case kPython:
            return createPythonNode();
        default:
            throw NodeCreationError(m_library.getName(), m_name, "Unknown library type");
    }
}

Node* NodeInfo::createNativeNode() {
    NodeCreator creator = (NodeCreator)m_data;
    return creator();
}

Node* NodeInfo::createPythonNode() {
    PyObject* node_obj = PyType_GenericNew((PyTypeObject*)m_data, NULL, NULL);
    // Decreffing the obj is the task of the new PythonNode obj.
    return new PythonNode(node_obj);
}

} // namespace NodeCore