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

#include "connection.h"
#include "parameter.h"
#include "node.h"

namespace NodeCore {

Connection::Connection(Parameter *outputParameter, Parameter *inputParameter)
           : m_output(outputParameter), m_input(inputParameter)
{
    assert(outputParameter->isOutputParameter());
    assert(inputParameter->isInputParameter());
}

Connection::~Connection()
{
}

Parameter* Connection::outputParameter() const
{
    return m_output;
}

Node* Connection::outputNode() const
{
    if (!hasOutput()) return NULL;
    return m_output->node();
}

Parameter* Connection::inputParameter() const
{
    return m_input;
}

Node* Connection::inputNode() const
{
    return m_input->node();
}

bool Connection::hasOutput() const
{
    // The output parameter can be set to null by the output node when it is deleting itself.
    return m_output != 0;
}

//std::ostream& operator<<(std::ostream& o, const Connection& c)
//{
//    o << "Connection(" << c.getOutputNode()->getName() << " -> " << c.getInputNode()->getName() << "." << c.m_input->getName() << ")";
//    return o;
//}

void Connection::update()
{
    m_output->node()->update();
}

void Connection::markDirtyDownstream()
{
    inputNode()->markDirty();
}

} // namespace NodeCore