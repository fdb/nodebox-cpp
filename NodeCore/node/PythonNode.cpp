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
#include "PythonNode.h"

namespace NodeCore {

PythonNode::PythonNode(PyObject* pythonObject)
          : Node(kPyObject), 
            m_pythonObject(pythonObject)
{
}

PythonNode::~PythonNode()
{
    Py_DECREF(m_pythonObject);
}

void PythonNode::process()
{
    PyObject* str =  PyObject_Str(m_pythonObject);
    std::cout << "[PN] Processing " << PyString_AsString(str) << std::endl;
    Py_DECREF(str);
    // Clear all errors before running
    PyErr_Clear();
    PyObject* result = PyObject_CallMethod(m_pythonObject, "process", NULL);
    if (!result) {
        std::cerr << "[PN] TestNode.process gave an error." << std::endl;
        if (PyErr_Occurred()) {
            PyErr_Print();
        }
        //throw new NodeProcessingError(
        return;
    }
    if (result != Py_None) {
        std::cerr << "[PN] [WARN] TestNode.process didn't return None." << std::endl;
        Py_DECREF(result);
        return;
    }
    Py_DECREF(result);
}

} // namespace NodeCore