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
#include "Parameter.h"

#include "Node.h"

namespace NodeCore {

Parameter::Parameter(Node *node, const ParameterName& name, const ParameterType& type, Channel channels, ParameterDirection direction)
     : m_node(node),
       m_name(name),
       m_verboseName(""),
       m_type(type),
       m_direction(direction),
       m_connection(0),
       m_channelCount(channels),
       m_channels(new Value[channels])
{
    if (validName(name)) {
        m_name = name;
    } else {
        throw InvalidName();
    }
    
    if (channels <= 0) {
        throw InvalidName();
    }
    
    for (Channel i=0; i<m_channelCount;++i) {        
        if (m_type == kInt) {
            m_channels[i].i = 0;
        } else if (m_type == kFloat) {
            m_channels[i].f = 0;
        } else if (m_type == kString) {
            m_channels[i].s = new std::string;
        } else {
            m_channels[i].d = 0;
        }
    }
}

Parameter::~Parameter()
{
    // TODO: strings don't get cleaned up, data may get cleaned up too soon.
    delete m_channels;
    disconnect();
}

int Parameter::asInt(Channel channel)
{
    if (m_type == kInt) {
        return m_channels[channel].i;
    } else if (m_type == kFloat) {
        return (int) m_channels[channel].f;
    } else {
        return 0;
    }
}

float Parameter::asFloat(Channel channel)
{
    if (m_type == kFloat) {
        return m_channels[channel].f;
    } else if (m_type == kInt) {
        return (float) m_channels[channel].i;
    } else {
        return 0;
    }
}

std::string Parameter::asString(Channel channel)
{
    if (m_type == kString) {
        return *m_channels[channel].s;
    } else {
        return "";
    }
}

void* Parameter::asData(Channel channel)
{
    return m_channels[channel].d;
}

void Parameter::set(int i, Channel channel)
{
    if (channel < 0 || channel >= m_channelCount) {
        throw ValueError("Invalid channel " + channel);
    }
    if (m_type == kInt) {
        // TODO: lazy setting
        preSet();
        m_channels[channel].i = i;
        postSet();
    } else {
        throw ValueError("Tried setting int value on parameter with type " + m_type);
    }
}

void Parameter::set(float f, Channel channel)
{
    if (channel < 0 || channel >= m_channelCount) {
        throw ValueError("Invalid channel " + channel);
    }
    if (m_type == kFloat) {
        // TODO: lazy setting
        preSet();
        m_channels[channel].f = f;
        postSet();
    } else {
        throw ValueError("Tried setting float value on parameter with type " + m_type);
    }
}

void Parameter::set(const std::string& s, Channel channel)
{
    if (channel < 0 || channel >= m_channelCount) {
        throw ValueError("Invalid channel " + channel);
    }
    if (m_type == kString) {
        // TODO: lazy setting
        preSet();
        delete m_channels[channel].s;
        m_channels[channel].s = new std::string(s);
        postSet();
    } else {
        throw ValueError("Tried setting string value on parameter with type " + m_type);
    }
}

void Parameter::set(void* data, Channel channel)
{  
    if (channel < 0 || channel >= m_channelCount) {
        throw ValueError("Invalid channel " + channel);
    }
    // TODO: lazy setting
    preSet();
    m_channels[channel].d = data;
    postSet();
}

bool Parameter::validName(const ParameterName& name)
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

// Checks if this parameter can connect to the ouput of the given node.
// This compares the types of the relevant input and output parameters.
bool Parameter::canConnectTo(Node* node)
{
    if (isOutputParameter()) return false;
    return  node->getOutputParameter()->getType() == getType();
}

Connection* Parameter::connect(Node* node)
{
    // Sanity check
    if (!isInputParameter()) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": can only connect input nodes");        
    }
    if (node == m_node) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": cannot connect to myself");
    }
    if (!canConnectTo(node)) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": cannot connect to " + node->getName());
    }
    disconnect();
    m_connection = new Connection(node->getOutputParameter(), this);
    node->addDownstream(m_connection);
    m_node->markDirty();
    // TODO: notify
    return m_connection;
}

bool Parameter::disconnect()
{
    assert(isInputParameter()); // TODO: also support disconnecting output parameters.
    if (!isConnected()) return false;
    if (m_connection->hasOutput()) {
        assert(m_connection->getOutputNode()->isOutputConnectedTo(this));
        m_connection->getOutputNode()->removeDownstream(m_connection);
    }
    delete m_connection;
    m_connection = 0;
    revertToDefault();
    m_node->markDirty();
    // TODO: dispatch/notify
    return true;
}

bool Parameter::isConnected()
{
    return m_connection != 0;
}

bool Parameter::isConnectedTo(Node* node)
{
    if (!m_connection)
        return false;
    return m_connection->getOutputNode() == node;
}

Connection* Parameter::getConnection()
{
    return m_connection;
}

void Parameter::update()
{
    if (isConnected()) {
        m_connection->getOutputNode()->update();
        assert(m_connection->getOutputParameter()->getType() == getType());
        if (m_type == kInt) {
            set(m_connection->getOutputParameter()->asInt());
        } else if (m_type == kFloat) {
            set(m_connection->getOutputParameter()->asFloat());
        } else if (m_type == kString) {
            set(m_connection->getOutputParameter()->asString());
        } else {
            set(m_connection->getOutputParameter()->asData());
        }
    }
}

std::ostream& operator<<(std::ostream& o, const Parameter& f)
{

    o << "Parameter(" << f.m_node->getName() << ", " << f.m_name << ", " << f.m_type << ")";
    return o;
}

void Parameter::revertToDefault()
{
    for (Channel i=0; i<m_channelCount;++i) {        
        if (m_type == kInt) {
            m_channels[i].i = 0;
        } else if (m_type == kFloat) {
            m_channels[i].f = 0;
        } else if (m_type == kString) {
            m_channels[i].s = new std::string;
        } else {
            // Don't do anything for kData or others.
            // TODO: this should ask the node to revert the data.
            // The node is the only one who knows how to treat opaque data.
        }
    }
}

void Parameter::preSet()
{
    // TODO: validate
}

void Parameter::postSet()
{
    m_node->markDirty();
}

} // namespace NodeCore