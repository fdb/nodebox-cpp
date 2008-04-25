#include <iostream>

#include "NodeCore.h"

namespace NodeCore {

Connection::Connection(Field *outputField, Field *inputField)
           : m_output(outputField), m_input(inputField)
{
}

Connection::~Connection()
{
}

void Connection::update()
{
    getOutputNode()->update();
}

Field* Connection::getOutputField()
{
    return m_output;
}

Node* Connection::getOutputNode()
{
    return m_output->getNode();
}

Field* Connection::getInputField()
{
    return m_input;
}

Node* Connection::getInputNode()
{
    return m_input->getNode();
}

std::ostream& operator<<(std::ostream& o, const Connection& c)
{
    o << "Connection(" << c.m_output << " -> " << c.m_input << ")";
    return o;
}

void Connection::markDirtyDownstream()
{
    getInputNode()->markDirty();
}

} // namespace NodeCore