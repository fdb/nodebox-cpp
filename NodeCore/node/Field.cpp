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

Field::Field(Node *node, const FieldName& name, FieldPolarity polarity)
     : m_node(node), 
       m_name(name), 
       m_polarity(polarity), 
       m_verboseName(""), 
       m_connectable(false),
       m_required(false),
       m_multi(false),
       m_connection(NULL)
{
    if (validName(name)) {
        m_name = name;
    } else {
        throw InvalidName();
    }
}

Field::~Field()
{
    if (m_polarity == kIn) {
        disconnect();
    }
}

bool Field::validName(const FieldName& name)
{
/*
    // Only lowercase letters, digits and underscore. Start with letter or underscore.
    // Minimum 1 characters, maximum 30 characters.
    static boost::regex nameRe("^[a-z_][a-z0-9_]{0,29}$");
    // No double underscore names (__reserved)
    static boost::regex doubleUnderScoreRe("^__.*$");
    // No reserved words
    static boost::regex reservedRe("^(?:node|process|name|x|y|dirty)$");
    return boost::regex_match(name, nameRe) 
           && (!boost::regex_match(name, doubleUnderScoreRe)) 
           && (!boost::regex_match(name, reservedRe));
*/
	return true;
}

bool Field::isConnected()
{
    if (m_polarity == kIn) {
        return m_connection != NULL;
    } else {
        return !m_downstreams.empty();
    }
}

bool Field::isConnectedTo(Field* field) {
    if (m_polarity == kOut) {
        for (DownstreamIterator iter = m_downstreams.begin(); iter != m_downstreams.end(); ++iter) {
            if (field == (*iter)->getInputField()) return true;
        }
        return false;
    } else {
        if (m_connection == NULL) return false;
        return m_connection->getOutputField() == field;
    }
}

Connection* Field::connect(Node *outputNode)
{
    // Sanity checks
    if (m_polarity == kOut) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": invoke connect only from the input");
    }
    if (outputNode == m_node) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": cannot connect to myself");
    }
    
    if (isConnected()) {
        disconnect();
    }
    m_connection = new Connection(outputNode->getOutputField(), this);
    outputNode->getOutputField()->m_downstreams.push_back(m_connection);
    m_node->markDirty();
    // TODO: dispatch/notify
    return m_connection;
}

bool Field::disconnect(Node *outputNode)
{
    if (m_polarity == kOut) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": invoke disconnect only from the input");
    }
    
    if (!isConnected()) return false;
    
    assert(outputNode->getOutputField()->isConnectedTo(this));
    outputNode->getOutputField()->removeFromDownstreams(m_connection);
    delete m_connection;
    m_connection = NULL;
    m_node->markDirty();
    revertToDefault();
    // TODO: dispatch/notify
    return true;
}

bool Field::disconnect()
{
    if (m_polarity == kOut) {
        throw ConnectionError(m_node->getName() + "." + m_name + ": invoke disconnect only from the input");
    }
    if (!isConnected()) return false;
    return disconnect(m_connection->getOutputNode());
}

Connection* Field::getConnection()
{
    assert (m_polarity == kIn);
    return m_connection;
}

void Field::removeFromDownstreams(Connection* conn)
{
    for (DownstreamIterator iter = m_downstreams.begin(); iter != m_downstreams.end(); ++iter) {
        if (conn == (*iter)) {
            m_downstreams.erase(iter);
            return;
        }
    }
    // We should have removed the connection from the downstreams.
    assert(false);
}

std::ostream& operator<<(std::ostream& o, const Field& f)
{
    o << "Field(" << f.m_node->getName() << "." << f.m_name << ")";
    return o;
}

void Field::preSet()
{
    if (m_polarity == kOut) {
        return;
        // TODO: find a way to check whether the value was set from processing, which is the
        //       only place the value can be set from.
        // throw ValueError("Output fields cannot be set directly, only through updating.");
    }
    if (isConnected()) {
        throw ValueError("Field '" + m_name + "' is connected.");
    }
    // TODO: validate
}

void Field::postSet()
{
    m_node->markDirty();
}

void Field::update()
{
    if (m_polarity == kIn) {
        if (isConnected()) {
            m_connection->update();
            setValueFromConnection();
        }
    } else {
        m_node->update();
    }
}

void Field::markDirty()
{
    assert(m_polarity == kOut);
    for (DownstreamIterator iter = m_downstreams.begin(); iter != m_downstreams.end(); ++iter) {
        (*iter)->markDirtyDownstream();
    }
}

} // namespace NodeCore