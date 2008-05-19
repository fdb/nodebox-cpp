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
#include "Node.h"

#include "Network.h"
#include "stringutils.h"

namespace NodeCore {

Node::Node(const FieldType& outputType)
    :
    m_x(0),
    m_y(0),
    m_name(""), // This should go to defaultName(), but you can't call virtuals in ctors.
    m_network(NULL),
    m_fields(FieldMap()),
    m_outputField(0),
    m_downstreams(ConnectionList()),
    m_dirty(true)
{
    m_outputField = new Field(this, "out", outputType, kOut);
}

Node::~Node()
{
    for (FieldIterator iter = m_fields.begin(); iter != m_fields.end(); ++iter) {
        delete (*iter).second;
    }
}

//// Naming

NodeName Node::defaultName() const
{
    return string_to_lower(className());
}

std::string Node::getName() const
{
    if (m_name == "") {
        return defaultName();
    } else {
        return m_name;
    }
}

void Node::setName(const NodeName& name)
{
    if (m_network) {
        m_network->rename(this, name);
    } else {
        _setName(name);
    }
}

void Node::_setName(const NodeName& name)
{    
    if (validName(name)) {
        m_name = name;
    } else {
        throw InvalidName();
    }
}

bool Node::validName(const NodeName& name)
{
    regex_t nameRe, doubleUnderScoreRe;

    // Only lowercase letters, digits and underscore. Start with letter or underscore.
    // Minimum 1 characters, maximum 30 characters.
    regcomp(&nameRe, "^[a-z_][a-z0-9_]{0,29}$", REG_EXTENDED|REG_NOSUB);

    // No double underscore names (__reserved)
    regcomp(&doubleUnderScoreRe, "^__.*$", REG_EXTENDED|REG_NOSUB);

    return regexec(&nameRe, name.c_str(), 0, NULL, 0) == 0 &
           regexec(&doubleUnderScoreRe, name.c_str(), 0, NULL, 0) != 0;
}

//// Network

void Node::setNetwork(Network* network)
{
    if (m_network && m_network != network) {
        m_network->remove(this);
    }
    if (network) {
        // Network->add checks if this node was already added in the network,
        // so we don't need to check it here.
        network->add(this);
    }
}

Network* Node::getNetwork()
{
    return m_network;
}

//// X/Y position

void Node::setX(float x)
{
    m_x = x;
    // TODO: notify
}

void Node::setY(float y)
{
    m_y = y;
    // TODO: notify
}

Field* Node::addField(const FieldName &name, const FieldType& type)
{
    if (hasField(name)) { throw InvalidName(); }
    Field *f = new Field(this, name, type);
    m_fields[name] = f;
    markDirty();
    return f;
}

Field* Node::getField(const FieldName &name) const
{
    if (hasField(name)) {
        FieldMap* fields = const_cast<FieldMap*>(&m_fields);
        return (*fields)[name];
    } else {
        throw FieldNotFound(name);
    }
}

bool Node::hasField(const FieldName &name) const
{
    return m_fields.count(name) == 1;
}

// Value shortcuts
int Node::asInt(const FieldName &name)
{
    return getField(name)->asInt();
}

float Node::asFloat(const FieldName &name)
{
    return getField(name)->asFloat();
}

std::string Node::asString(const FieldName &name)
{
    return getField(name)->asString();
}

void* Node::asData(const FieldName &name)
{
    return getField(name)->asData();
}

int Node::outputAsInt() const
{
    return m_outputField->asInt();
}

float Node::outputAsFloat() const
{
    return m_outputField->asFloat();
}

std::string Node::outputAsString() const
{
    return m_outputField->asString();
}

void* Node::outputAsData() const
{
    return m_outputField->asData();
}

void Node::set(const FieldName &name, int i)
{
    getField(name)->set(i);
}

void Node::set(const FieldName &name, float f)
{
    getField(name)->set(f);
}

void Node::set(const FieldName &name, const std::string& s)
{
    getField(name)->set(s);
}

void Node::set(const FieldName &name, void* d)
{
    getField(name)->set(d);
}

void Node::update()
{
    if (m_dirty) {
        for (FieldIterator iter = m_fields.begin(); iter != m_fields.end(); ++iter) {
            Field* f = (*iter).second;
            f->update();
        }
        process();
        m_dirty = false;
    }
}

bool Node::isDirty() const
{
    return m_dirty;
}

void Node::markDirty()
{
    if (m_dirty) return;
    m_dirty = true;
    for (ConnectionIterator iter = m_downstreams.begin(); iter != m_downstreams.end(); ++iter) {
        Connection* conn = (*iter);
        conn->getInputNode()->markDirty();
    }
    if (m_network && !m_network->isDirty()) {
        // TODO: this is not ideal, since only changes to the rendered node should
        // make the network dirty.
        m_network->markDirty();
    }
    // TODO: dispatch/notify
}

bool Node::isOutputConnected()
{
    return m_downstreams.size() > 0;
}

bool Node::isOutputConnectedTo(Node* node)
{
    for (ConnectionIterator iter = m_downstreams.begin(); iter != m_downstreams.end(); ++iter) {
        if ((*iter)->getInputNode() == node)
            return true;
    }
    return false;
}

bool Node::isOutputConnectedTo(Field* field)
{
    for (ConnectionIterator iter = m_downstreams.begin(); iter != m_downstreams.end(); ++iter) {
        if ((*iter)->getInputField() == field)
            return true;
    }
    return false;
}

ConnectionList Node::getOutputConnections()
{
    return m_downstreams;
}

void Node::process()
{
    // This space intentionally left blank.
}

void Node::setOutput(int i)
{
    m_outputField->set(i);
}

void Node::setOutput(float f)
{
    m_outputField->set(f);
}

void Node::setOutput(std::string s)
{
    m_outputField->set(s);
}

void Node::setOutput(void* d)
{
    m_outputField->set(d);
}

void Node::addDownstream(Connection* c)
{
    // TODO: Check if the connection/field is already in the list.
    assert (c != 0);
    assert (c->getOutputNode() == this);
    assert (c->getInputNode() != this);
    m_downstreams.push_back(c);
}

void Node::removeDownstream(Connection* c)
{
    assert (c != 0);
    for (ConnectionIterator iter = m_downstreams.begin(); iter != m_downstreams.end(); ++iter) {
        if (*iter == c) {
            m_downstreams.erase(iter);
            return;
        }
    }
    std::cout << m_name <<": could not remove connection" << c << std::endl;
    assert(false);
}

std::ostream& operator<<(std::ostream& o, const Node& n)
{
    o << "Node(" << n.m_name << ")";
    return o;
}

} // namespace NodeCore