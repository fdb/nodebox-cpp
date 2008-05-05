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

namespace NodeCore {

Node::Node()
    :
    m_x(0),
    m_y(0),
    m_name(""), // This should go to defaultName(), but you can't call virtuals in ctors.
    m_network(NULL),
    m_fields(FieldMap()),
    m_downstreams(ConnectionList()),
    m_dirty(true)
{
}

Node::~Node()
{
    for (FieldIterator iter = m_fields.begin(); iter != m_fields.end(); ++iter) {
        delete (*iter).second;
    }
}

//// Naming

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
        network->add(this);
    }
}

Network* Node::getNetwork()
{
    return m_network;
}

Field* Node::addField(const FieldName &name, FieldType type)
{
    if (hasField(name)) { throw InvalidName(); }
    Field *f = new Field(this, name, type);
    m_fields[name] = f;
    return f;
}

Field* Node::getField(const FieldName &name)
{
    if (hasField(name)) {
        Field* f = m_fields[name];
        return f;
    } else {
        throw FieldNotFound(name);
    }
}

bool Node::hasField(const FieldName &name)
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

void Node::set(const FieldName &name, int i)
{
    getField(name)->set(i);
}

void Node::set(const FieldName &name, float f)
{
    getField(name)->set(f);
}

void Node::set(const FieldName &name, std::string s)
{
    getField(name)->set(s);
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

void Node::process()
{
    // This space intentionally left blank.
}

// Updates a connected field with the output value of this node.
// This method gets called whenever a downstream node wants to update
// the values of its connected fields.
// Since we don't know anything about the output value of a node,
// it is very important that overriding nodes implement this method.
void Node::updateField(Field* f)
{
}

// This method will be checked before connecting a field.
// It reports whether the output of this node can be connected
// to the specified field.
// By default, it returns false: overriding nodes should implement
// this method and do proper checking.
bool Node::canConnectTo(Field* f) const
{
    return false;
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