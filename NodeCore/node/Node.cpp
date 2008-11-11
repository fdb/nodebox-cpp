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
#include "Node.h"
#include "Network.h"

#include <QtCore/QStringList>

namespace NodeCore {

Node::Node(NodeType* type, const QString& name)
    : m_type(type),
      m_network(NULL),
      m_x(0),
      m_y(0),
      m_dirty(true)
{
    if (name == NULL) {
        m_name = m_type->defaultName();
    } else {
        m_name = name;
    }
    for (int i=0; i<m_type->parameterTypeCount(); ++i) {
        ParameterType* pType = m_type->parameterTypeAt(i);
        Parameter* param = pType->createParameter(this);
        m_parameters[pType->name()] = param;
    }
    m_outputParameter = qobject_cast<OutputParameter*>(m_type->outputParameterType()->createParameter(this));
    // Whenever the node type is reloaded, it sends out a signal. Use that
    // to mark the node as dirty.
    // TODO: implement this as a signal.
    // dispatcher.connect(self._reloaded, signal=signals.node_type_reloaded)
}

Node::~Node()
{
    QList<Parameter*> params = m_parameters.values();
    for (int i=0; i<params.size(); ++i) {
        delete params[i];
    }
    delete m_outputParameter;
}

void Node::setPosition(const QPointF& p)
{
    m_x = p.x();
    m_y = p.y();
    // emit signal
}

void Node::setX(qreal x)
{
    setPosition(QPointF(x, m_y));
}

void Node::setY(qreal y)
{
    setPosition(QPointF(m_x, y));
}

void Node::setName(const QString& name)
{
    if (inNetwork()) {
        network()->rename(this, name);
    } else {
        if (name.isEmpty()) return;
        if (NodeType::isValidName(name)) {
            QString old_name = m_name;
            m_name = name;
            // TODO: signal
            // dispatcher.send(signal=signals.node_renamed, sender=self, node=self, old_name=old_name, name=name)
        }
    }
}

QList<Parameter*> Node::parameters() const
{
    // Parameters are stored in a map, and are not ordered.
    // The correct order is that of ParameterTypes in the NodeType.
    QList<Parameter*> parameters;
    for (int i=0; i<m_type->parameterTypeCount(); ++i) {
        ParameterType* pType = m_type->parameterTypeAt(i);
        Parameter* param = m_parameters[pType->name()];
        parameters.append(param);
    }
    return parameters;
}

QVariantList Node::values(const QString& parameterName) const
{
    if (!m_parameters.contains(parameterName)) return QVariantList();
    return m_parameters[parameterName]->values();
}

void
Node::setValues(const QString& parameterName, const QVariantList& values)
{
    if (!m_parameters.contains(parameterName)) return;
    m_parameters[parameterName]->setValues(values);
}

QVariantList Node::outputValues() const
{
    return m_outputParameter->values();
}

QList<Parameter*> Node::compatibleParameters(Node* outputNode) const
{
    QList<Parameter*> params;
    for (int i=0; i<m_parameters.count(); ++i) {
        Parameter* param = m_parameters.values()[i];
        if (param->canConnect(outputNode)) {
            params.append(param);
        }
    }
    return params;
}

/*! Removes all connections from and to this node.
    Returns true if any connections were removed.
*/
bool Node::disconnect()
{
    bool removedSomething = false;

    // Disconnect all inputs
    for (int i=0; i<m_parameters.count(); ++i) {
        Parameter* param = m_parameters.values()[i];
        removedSomething = param->disconnect() | removedSomething;
    }

    // Disconnect all outputs
    // Copy the list of downstreams, since you will be removing elements
    // from it while iterating.
    QList<Connection*> downstreams = m_outputParameter->m_downstreams;
    for (int i=0; i<downstreams.count(); ++i) {
        Connection* conn = downstreams.at(i);
        removedSomething = conn->inputParameter()->disconnect() | removedSomething;
    }

    return removedSomething;
}

bool Node::isConnected()
{
    // Check parameters for upstream connections.
    for (int i=0; i<m_parameters.count(); ++i) {
        Parameter* param = m_parameters.values()[i];
        if (param->isConnected())
            return true;
    }
    // Check output parameter for downstream connections.
    return m_outputParameter->isConnected();
}

/*! Updates the node by processing all required dependencies.
    This method will process only dirty nodes.
    This operation can take a long time, and should be run in a separate thread.
*/
void Node::update()
{
    if (!isDirty())
        return;
    for (int i=0; i<m_parameters.count(); ++i) {
        Parameter* param = m_parameters.values()[i];
        param->update();
    }
    // TODO: Catch exception here.
    bool success = process();
    m_dirty = false;
    // TODO: signal
    // dispatcher.send(signal=signals.node_updated, sender=self, node=self)
}

void Node::markDirty(bool forced)
{
    if (m_dirty && !forced) return;
    m_dirty = true;
    m_outputParameter->markDirtyDownstream();
    if (inNetwork()) {
        // Mark the network as dirty if it is not dirty already.
        // The force flag overrides this, and makes the network
        // dirty regardless.
        if (!m_network->isDirty() || forced) {
            // Only changes to the rendered node should make the network dirty.
            // TODO: Check for corner cases.
            if (m_network->renderedNode() == this)
                m_network->markDirty(forced);
        }
    }
    // TODO: dispatcher.send(signal=signals.node_marked_dirty, sender=self, node=self)
}

/*! Do the actual processing for this node.

    Implementing nodes will want to override this.
    This method can return either true or false:
    - true: if no processing errors occurred. The output of this node should be set
    (using _setOutput).
    - false: if errors occurred. The error should be set (using setError).
*/
bool Node::process()
{
    return true;
}

void Node::setOutputValues(const QVariantList& values)
{
    m_outputParameter->m_values = values;
}

void Node::setError(const QString& error)
{
    m_error = error;
    // TODO: signal?
}

void Node::setNetwork(Network* network)
{
    Network* oldNetwork = m_network;
    if (m_network != NULL)
        m_network->remove(this);
    if (network != NULL)
        m_network->add(this);
   // TODO: dispatcher.send(signal=signals.node_changed_network, sender=self, node=self, old_network=old_network, network=network)
}
Network* Node::rootNetwork() const
{
    if (!inNetwork()) return NULL;
    Network* network = m_network;
    while (network->network() != NULL)
        network = network->network();
   return network;
}

bool Node::isRendered() const
{
    if (!inNetwork()) return false;
    return m_network->renderedNode() == this;
}

void Node::setRendered()
{
    if (!inNetwork()) return;
    m_network->setRenderedNode(this);
    // TODO: dispatcher.send(signal=signals.node_set_rendered, sender=self, node=self)
}

QString Node::networkPath()
{
    QStringList parts;
    parts << m_name;
    Network* network = m_network;
    while (network != NULL) {
        parts << network->name();
        network = network->network();
    }
    return parts.join(QString("/"));
}

/*! Reloads the library that implements this node.

    Afterwards, this node, all others of its type,
    and all other instances of types in this library will
    be marked dirty.
*/
void Node::reload()
{
    // TODO: implement
}

/*! This method will get called whenever the node type is reloaded. */
void Node::reloadEvent()
{
    markDirty();
    // TODO: dispatcher.send(signal=signals.node_reloaded, sender=self, node=self)
}

} // namespace NodeCore
