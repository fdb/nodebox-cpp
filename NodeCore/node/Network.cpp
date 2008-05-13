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
#include "Network.h"

namespace NodeCore {

Network::Network(const FieldType& outputType)
       : Node(outputType),
         m_nodes(NodeMap()),
         m_renderedNode(NULL)
{
}

Network::~Network()
{
    // Delete all nodes in the node map
    for (NodeIterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter) {
        delete (*iter).second;
    }
}

//// Container operations

bool Network::isEmpty()
{
    return m_nodes.empty();
}

unsigned int Network::size()
{
    return m_nodes.size();
}

std::string Network::setUniqueNodeName(Node* node)
{
    assert(contains(node));
    int counter = 1;
    while (true) {
        std::string suggestedName = node->defaultName();
        suggestedName += counter;
        if (!contains(suggestedName)) {
            rename(node, suggestedName);
            return suggestedName;
        }
        ++counter;
    }
}

// throws DuplicateName if a node with this name is already in the network.
// Nodes in this network will be automatically deleted.
bool Network::add(Node* node)
{
    assert(node != NULL);
    if (contains(node)) {
        return false;
    }
    if (m_nodes.count(node->getName()) == 1) {
        throw DuplicateName(node, node->getName());
    }
    assert(m_nodes.count(node->getName()) == 0);
    node->m_network = this;
    m_nodes[node->getName()] = node;
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
    m_nodes.erase(node->getName());
    if (m_renderedNode == node)
        setRenderedNode(NULL);
    // TODO: notify
    return true;
}

bool Network::contains(Node* node)
{
    if (node == NULL) return false;
    return m_nodes.count(node->getName()) == 1;
}

bool Network::contains(const NodeName& name)
{
    return getNode(name) != NULL;
}

Node* Network::getNode(const NodeName& name)
{
    return m_nodes[name];
}

bool Network::rename(Node* node, const NodeName& name)
{
    assert(contains(node));
    if (node->getName() == name) return true;
    if (contains(name)) return false;
    m_nodes.erase(node->getName());
    node->_setName(name);
    m_nodes[name] = node;
    return true;
}

//// Rendered node

Node* Network::getRenderedNode() const
{
    return m_renderedNode;
}

void Network::setRenderedNode(Node* node)
{
    if (node != NULL && !contains(node)) {
        throw NodeNotInNetwork(this, node);
    }
    if (m_renderedNode == node) return;
    m_renderedNode = node;
    markDirty();
}

std::ostream& operator<<(std::ostream& o, const Network& n)
{
    o << "Network(" << n.getName() << ")";
    return o;
}

//// Protected methods

void Network::process()
{
    if (m_renderedNode == NULL) {
        throw NodeProcessingError(this, "No node to render");
    }
    assert(contains(m_renderedNode));
    m_renderedNode->update();
    if (m_renderedNode->getOutputType() == kInt) {
        setOutput(m_renderedNode->outputAsInt());
    } else if (m_renderedNode->getOutputType() == kFloat) {
        setOutput(m_renderedNode->outputAsFloat());
    } else if (m_renderedNode->getOutputType() == kString) {
        setOutput(m_renderedNode->outputAsString());
    } else {
        setOutput(m_renderedNode->outputAsData());
    }
}

} // namespace NodeCore