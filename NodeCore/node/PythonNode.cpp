#include "NodeCore.h"

namespace NodeCore {

PythonNode::PythonNode(PyObject* pythonObject) : m_pythonObject(pythonObject)
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