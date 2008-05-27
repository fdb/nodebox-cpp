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
#include "Connection.h"

#include "Field.h"
#include "Node.h"

namespace NodeCore {

Connection::Connection(Field *outputField, Field *inputField)
           : m_output(outputField), m_input(inputField)
{
    assert(outputField->isOutputField());
    assert(inputField->isInputField());
}

Connection::~Connection()
{
}

Field* Connection::getOutputField() const
{
    return m_output;
}

Node* Connection::getOutputNode() const
{
    if (!hasOutput()) return NULL;
    return m_output->getNode();
}

Field* Connection::getInputField() const
{
    return m_input;
}

Node* Connection::getInputNode() const
{
    return m_input->getNode();
}

bool Connection::hasOutput() const
{
    // The output field can be set to null by the output node when it is deleting itself.
    return m_output != 0;
}

std::ostream& operator<<(std::ostream& o, const Connection& c)
{
    o << "Connection(" << c.getOutputNode()->getName() << " -> " << c.getInputNode()->getName() << "." << c.m_input->getName() << ")";
    return o;
}

void Connection::markDirtyDownstream()
{
    getInputNode()->markDirty();
}

} // namespace NodeCore