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

#include "config.h"
#include "NodeInfo.h"

#include "NodeLibrary.h"
#include <Python/Python.h>

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
        default:
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

typedef struct swig_type_info *(*swig_dycast_func)(void **);

typedef struct {
  PyObject_HEAD
  void *ptr;
  swig_type_info *ty;
  int own;
  PyObject *next;
} PySwigObject;

Node* NodeInfo::createPythonNode() {
    PyObject* node_obj = PyType_GenericNew((PyTypeObject*)m_data, NULL, NULL);
    PyObject_Print(node_obj, stderr, Py_PRINT_RAW);
    PyObject* node_this = PyObject_GetAttrString(node_obj, "this");
    if (!node_this) {
        std::cout << "no node.this" << std::endl;
        return 0;
    }
    std::cout << "node.this" << std::endl;

    PySwigObject* swigger = reinterpret_cast<PySwigObject*> (node_this);
    Node* node_native = reinterpret_cast<Node*> (swigger->ptr);
    return node_native;
    //swigger
    // Decreffing the obj is the task of the new PythonNode obj.
    //return new PythonNode(node_obj);
}

} // namespace NodeCore