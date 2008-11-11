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

#include "Connection.h"
#include "Parameter.h"
#include "Network.h"
#include "Node.h"

namespace NodeCore {

Parameter::Parameter(ParameterType* type, Node* node)
    : m_type(type),
      m_node(node),
      m_values(type->defaultValues())
{
}

Parameter::~Parameter()
{
    if (isConnected())
        disconnect();
}

void Parameter::setValues(const QVariantList& values)
{
    if (isConnected()) return;
    if (hasExpression()) return;
    if (m_values == values) return;
    if (!validate(values)) return;
    m_values = values;
    m_node->markDirty();
    // TODO: dispatch
}

bool Parameter::validate(const QVariantList& values)
{
    return m_type->validate(values);
}

void Parameter::revertToDefault()
{
    if (isConnected()) return;
    if (hasExpression()) return;
    m_values = m_type->defaultValues();
    m_node->markDirty();
}

void Parameter::setExpression(const QString& s)
{
    if (isConnected()) return;
    if (s.isEmpty()) {
        clearExpression();
    } else {
        // TODO: Parse expression
        // TODO: Create expression connections
        m_expression = s;
        createExpressionConnections();
        m_node->markDirty();
        // TODO: Send signal that expression changed
    }
}

void Parameter::clearExpression()
{
    if (!hasExpression()) return;
    m_expression = "";
    removeExpressionConnections();
    m_node->markDirty();
    // TODO: Send signal that expression changed
}

QList<Parameter*> Parameter::expressionDependencies() const
{
    return QList<Parameter*>();
}

Connection* Parameter::connect(Node* outputNode)
{
    Q_ASSERT(isInputParameter());
    if (m_node == outputNode) return NULL;
    if (isConnected())
        disconnect();
    m_connection = new Connection(outputNode->outputParameter(), this);
    outputNode->outputParameter()->m_downstreams.append(m_connection);
    // After the connection is made, check if it creates a cycle, and
    // remove the connection if it does.
    if (m_node->inNetwork()) {
        if (m_node->network()->containsCycles()) {
            disconnect();
            return NULL;
        }
    }
    // TODO: Send signal
    // dispatcher.send(signal=signals.parameter_connected, sender=self, parameter=self, output_node=output_node, connection=self._connection)
    m_node->markDirty();
    return m_connection;
}
bool Parameter::disconnect()
{
    Q_ASSERT(isInputParameter());
    if (!isConnected()) return false;
    Node* outputNode = m_connection->outputNode();
    Q_ASSERT(outputNode->outputParameter()->m_downstreams.contains(m_connection));
    outputNode->outputParameter()->m_downstreams.removeAll(m_connection);
    delete m_connection;
    m_connection = NULL;
    revertToDefault(); // This also marks the node dirty.
    // TODO: Signal
    // dispatcher.send(signal=signals.parameter_disconnected, sender=self, parameter=self, connection=old_connection, output_node=output_node)
    return true;
}
bool Parameter::canConnect(const Node* node) const
{
    return m_type->isCompatible(node);
}

bool Parameter::canConnect(const OutputParameter* p) const
{
    return m_type->isCompatible(p);
}

/*! Updates the parameter, making sure all dependencies are clean.

    This method can take a long time and should be run in a separate thread.
*/
void Parameter::update()
{
    if (isConnected()) {
        m_connection->outputNode()->update();
        // TODO: Validation errors are silently discarded.
        if (validate(m_connection->outputNode()->outputValues()))
            m_values = m_connection->outputNode()->outputValues();
    }
    if (hasExpression()) {
        for (int i=0; i<m_expressionConnections.size(); i++) {
            m_expressionConnections[i]->update();
        }
        QVariantList values = evaluateExpression();
        if (validate(values))
            m_values = values;
    }
}

QList<QScriptValue*> Parameter::expressionLocals()
{
    return QList<QScriptValue*>();
}

QList<QScriptValue*> Parameter::expressionGlobals()
{
    return QList<QScriptValue*>();
}

QVariantList Parameter::evaluateExpression()
{
    // TODO: Implement
    return QVariantList();
}

void Parameter::createExpressionConnections()
{
    // TODO: Implement
}

void Parameter::removeExpressionConnections()
{
    // TODO: Implement
}

} // namespace NodeCore
