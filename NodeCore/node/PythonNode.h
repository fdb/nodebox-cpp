#ifndef PythonNode_h
#define PythonNode_h

#include <iostream>
#include <Python/Python.h>

#include "Node.h"

namespace NodeCore {

class PythonNode : public Node
{
public:
    PythonNode(PyObject* pythonObject);
    virtual ~PythonNode();

    virtual void process();
    
private:
    PyObject* m_pythonObject;
};

} // namespace NodeCore

#endif // PythonNode_h
