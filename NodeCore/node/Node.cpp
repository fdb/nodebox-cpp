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

Node::Node(const ParameterType& outputType)
    :
    m_x(0),
    m_y(0),
    m_name(""), // This should go to defaultName(), but you can't call virtuals in ctors.
    m_network(NULL),
    m_parameters(ParameterMap()),
    m_outputParameter(0),
    m_downstreams(ConnectionList()),
    m_dirty(true)
{
    m_outputParameter = new Parameter(this, "out", outputType, 1, kOut);
}

Node::~Node()
{
    for (ParameterMapIterator iter = m_parameters.begin(); iter != m_parameters.end(); ++iter) {
        delete (*iter).second;
    }
    for (ConnectionIterator iter = m_downstreams.begin(); iter != m_downstreams.end(); ++iter) {
        Connection* conn = (*iter);
        conn->m_output = 0;
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

Parameter* Node::addParameter(const ParameterName &name, const ParameterType& type, Channel channels)
{
    if (hasParameter(name)) { throw InvalidName(); }
    Parameter *f = new Parameter(this, name, type, channels);
    m_parameters[name] = f;
    markDirty();
    return f;
}

Parameter* Node::getParameter(const ParameterName &name) const
{
    if (hasParameter(name)) {
        ParameterMap* parameters = const_cast<ParameterMap*>(&m_parameters);
        return (*parameters)[name];
    } else {
        throw ParameterNotFound(name);
    }
}

bool Node::hasParameter(const ParameterName &name) const
{
    return m_parameters.count(name) == 1;
}

ParameterList Node::getParameters()
{
    ParameterList parameterList = ParameterList();
    for (ParameterMapIterator iter = m_parameters.begin(); iter != m_parameters.end(); ++iter) {
        parameterList.push_back((*iter).second);
    }
    return parameterList;
}

// Value shortcuts
int Node::asInt(const ParameterName &name)
{
    return getParameter(name)->asInt();
}

float Node::asFloat(const ParameterName &name)
{
    return getParameter(name)->asFloat();
}

std::string Node::asString(const ParameterName &name)
{
    return getParameter(name)->asString();
}

void* Node::asData(const ParameterName &name)
{
    return getParameter(name)->asData();
}

int Node::outputAsInt() const
{
    return m_outputParameter->asInt();
}

float Node::outputAsFloat() const
{
    return m_outputParameter->asFloat();
}

std::string Node::outputAsString() const
{
    return m_outputParameter->asString();
}

void* Node::outputAsData() const
{
    return m_outputParameter->asData();
}

void Node::set(const ParameterName &name, int i)
{
    getParameter(name)->set(i);
}

void Node::set(const ParameterName &name, float f)
{
    getParameter(name)->set(f);
}

void Node::set(const ParameterName &name, const std::string& s)
{
    getParameter(name)->set(s);
}

void Node::set(const ParameterName &name, void* d)
{
    getParameter(name)->set(d);
}

void Node::update()
{
    if (m_dirty) {
        for (ParameterMapIterator iter = m_parameters.begin(); iter != m_parameters.end(); ++iter) {
            Parameter* f = (*iter).second;
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

bool Node::isOutputConnectedTo(Parameter* parameter)
{
    for (ConnectionIterator iter = m_downstreams.begin(); iter != m_downstreams.end(); ++iter) {
        if ((*iter)->getInputParameter() == parameter)
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

void Node::_setOutput(int i)
{
    m_outputParameter->set(i);
}

void Node::_setOutput(float f)
{
    m_outputParameter->set(f);
}

void Node::_setOutput(std::string s)
{
    m_outputParameter->set(s);
}

void Node::_setOutput(void* d)
{
    m_outputParameter->set(d);
}

void Node::addDownstream(Connection* c)
{
    // TODO: Check if the connection/parameter is already in the list.
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