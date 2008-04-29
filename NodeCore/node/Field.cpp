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
#include "Field.h"

#include "Node.h"

namespace NodeCore {

Field::Field(Node *node, const FieldName& name, const FieldType& type)
     : m_node(node), 
       m_name(name),
       m_verboseName(""),
       m_type(type),
       m_connection(0)
{
    if (validName(name)) {
        m_name = name;
    } else {
        throw InvalidName();
    }
    if (m_type == kInt) {
        m_value.i = 0;
    } else if (m_type == kFloat) {
        m_value.f = 0;
    } else if (m_type == kString) {
        m_value.s = new std::string;
    } else if (m_type == kData) {
        m_value.d = 0;
    }
}

int Field::asInt()
{
    if (m_type == kInt) {
        return m_value.i;
    } else if (m_type == kFloat) {
        return (int) m_value.f;
    } else {
        return 0;
    }
}

float Field::asFloat()
{
    if (m_type == kFloat) {
        return m_value.f;
    } else if (m_type == kInt) {
        return (float) m_value.i;
    } else {
        return 0;
    }
}

std::string Field::asString()
{
    if (m_type == kString) {
        return *m_value.s;
    } else {
        return "";
    }
}

void* Field::asData()
{
    if (m_type == kData) {
        return m_value.d;
    } else {
        return 0;
    }
}

void Field::set(int i)
{
    if (m_type == kInt) {
        preSet();
        m_value.i = i;
        postSet();
    } else {
        throw ValueError("Tried setting int value on field with type " + m_type);
    }
}

void Field::set(float f)
{
    if (m_type == kFloat) {
        preSet();
        m_value.f = f;
        postSet();
    } else {
        throw ValueError("Tried setting float value on field with type " + m_type);
    }
}

void Field::set(const std::string& s)
{
    if (m_type == kString) {
        preSet();
        delete m_value.s;
        m_value.s = new std::string(s);
        postSet();
    } else {
        throw ValueError("Tried setting string value on field with type " + m_type);
    }
}

void Field::set(void* data)
{  
    if (m_type == kData) {
        preSet();
        m_value.d = data;
        postSet();
    } else {
        throw ValueError("Tried setting data value on field with type " + m_type);
    }
}

Field::~Field()
{
    disconnect();
}

bool Field::validName(const FieldName& name)
{
    regex_t nameRe, doubleUnderScoreRe, reservedRe;

    // Only lowercase letters, digits and underscore. Start with letter or underscore.
    // Minimum 1 characters, maximum 30 characters.
    regcomp(&nameRe, "^[a-z_][a-z0-9_]{0,29}$", REG_EXTENDED|REG_NOSUB);

    // No double underscore names (__reserved)
    regcomp(&doubleUnderScoreRe, "^__.*$", REG_EXTENDED|REG_NOSUB);

    // No reserved words
    regcomp(&reservedRe, "^(node|name)$", REG_EXTENDED|REG_NOSUB);
    
    return regexec(&nameRe, name.c_str(), 0, NULL, 0) == 0 &
           regexec(&doubleUnderScoreRe, name.c_str(), 0, NULL, 0) != 0 &
           regexec(&reservedRe, name.c_str(), 0, NULL, 0) != 0;
}

Connection* Field::connect(Node* node)
{
    // Sanity check
    if (node == m_node) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": cannot connect to myself");
    }    
    disconnect();
    m_connection = new Connection(node, this);
    node->addDownstream(m_connection);
    m_node->markDirty();
    // TODO: notify
    return m_connection;
}

bool Field::disconnect()
{
    if (!isConnected()) return false;
    assert(m_connection->m_output->isOutputConnectedTo(this));
    m_connection->getOutputNode()->removeDownstream(m_connection);
    delete m_connection;
    m_connection = 0;
    revertToDefault();
    m_node->markDirty();
    // TODO: dispatch/notify
    return true;
}

bool Field::isConnected()
{
    return m_connection != 0;
}

bool Field::isConnectedTo(Node* node)
{
    if (!m_connection)
        return false;
    return m_connection->m_output == node;
}

Connection* Field::getConnection()
{
    return m_connection;
}

void Field::update()
{
    if (isConnected()) {
        m_connection->m_output->update();
        m_connection->m_output->updateField(this);
        // TODO: The output data of the upstream node becomes my value.
    }
}

std::ostream& operator<<(std::ostream& o, const Field& f)
{

    o << "Field(" << f.m_node->getName() << ", " << f.m_name << ", " << f.m_type << ")";
    return o;
}

void Field::revertToDefault()
{
    if (m_type == kInt) {
        m_value.i = 0;
    } else if (m_type == kFloat) {
        m_value.f = 0;
    } else if (m_type == kString) {
        delete m_value.s;
        m_value.s = new std::string;
    } else {
        // Don't do anything for kData or others.
        // TODO: this should ask the node to revert the data.
        // The node is the only one who knows how to treat opaque data.
    }
}

void Field::preSet()
{
    // TODO: validate
}

void Field::postSet()
{
    m_node->markDirty();
}

} // namespace NodeCore