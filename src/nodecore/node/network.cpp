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

#include "network.h"

namespace NodeCore {

Network::Network(NodeType* type, const QString& name)
       : Node(type, name),
         m_renderedNode(NULL)
{
}

Network::~Network()
{
    // TODO: Delete all nodes in the node map
    /*
    for (NodeMapIterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter) {
        delete (*iter).second;
    }
    */
}

//// Container operations

bool Network::isEmpty() const
{
    return m_nodes.empty();
}

int Network::size() const
{
    return m_nodes.size();
}

QString Network::setUniqueNodeName(Node* node)
{
    // The node doesn't have to be in the network, but it will
    // get a name that is unique for this network.
    int counter = 1;
    while (true) {
        QString suggestedName("%1%2");
        suggestedName.arg(node->nodeType()->defaultName());
        suggestedName.arg(counter);
        if (!contains(suggestedName)) {
            // We don't use rename here, since it assumes the node will be in this network.
            node->setName(suggestedName);
            return suggestedName;
        }
        ++counter;
    }
}

bool Network::rename(Node* node, const QString& name)
{
    assert(contains(node));
    if (node->name() == name) return true;
    if (contains(name)) return false;
    m_nodes.remove(node->name());
    node->m_name = name;
    m_nodes[name] = node;
    return true;
}

// throws DuplicateName if a node with this name is already in the network.
// Nodes in this network will be automatically deleted.
bool Network::add(Node* node)
{
    assert(node != NULL);
    if (contains(node)) {
        return false;
    }
    if (m_nodes.count(node->name()) == 1) {
        return false;
    }
    assert(m_nodes.count(node->name()) == 0);
    node->m_network = this;
    m_nodes[node->name()] = node;
    return true;
}

bool Network::remove(Node* node)
{
    assert(node != NULL);
    if (!contains(node))
        return false;
    node->markDirty();
    // TODO: Disconnect the node from the network
    node->m_network = NULL;
    m_nodes.remove(node->name());
    if (m_renderedNode == node)
        setRenderedNode(NULL);
    // TODO: notify
    return true;
}

bool Network::contains(Node* node) const
{
    if (node == NULL) return false;
    return contains(node->name());
}

bool Network::contains(const QString& name) const
{
    return m_nodes.contains(name);
}

Node* Network::node(const QString& name) const
{
    if (!contains(name)) return NULL;
    return m_nodes[name];
}

QList<Node*> Network::nodes() const
{
    QList<Node*> nodes;
    // TODO: iterate map
    /*
    NodeList nodes = NodeList();
    for (NodeMapIterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter) {
        nodes.push_back((*iter).second);
    }
    */
    return nodes;
}

//// Rendered node

Node* Network::renderedNode() const
{
    return m_renderedNode;
}

void Network::setRenderedNode(Node* node)
{
    if (node != NULL && !contains(node)) return;
    if (m_renderedNode == node) return;
    m_renderedNode = node;
    markDirty();
}

/*
std::ostream& operator<<(std::ostream& o, const Network& n)
{
    o << "Network(" << n.name() << ")";
    return o;
}
*/

bool Network::containsCycles() const
{
    // TODO: Implement CycleDetector
    return false;
}

//// Protected methods

bool Network::process()
{
    if (m_renderedNode == NULL) {
        setError("No node to render");
        return false;
    }
    Q_ASSERT(contains(m_renderedNode));
    m_renderedNode->update();
    if (m_renderedNode->hasError()) {
        setError(m_renderedNode->error());
        return false;
    }
    setOutputValues(m_renderedNode->outputValues());
    return true;
}

} // namespace NodeCore
