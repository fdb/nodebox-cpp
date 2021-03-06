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

#ifndef Network_h
#define Network_h

#include "Node.h"

#include <string>
#include <sstream>
#include <exception>
#include <iostream>
#include <map>

namespace NodeCore {

class DuplicateName : public std::exception
{
public:
    DuplicateName(Node* node, const NodeName& name) : m_node(node), m_name(name) {}
    DuplicateName(const DuplicateName& other) : m_node(other.m_node), m_name(other.m_name) {}
    virtual ~DuplicateName() throw () {}
    Node* getNode() { return m_node; }
    NodeName getName() { return m_name; }
    DuplicateName& operator=(const DuplicateName& other)
    {
        if(this == &other) return *this;
        m_node = other.m_node;
        m_name = other.m_name;
        return *this;
    }
private:
    Node* m_node;
    NodeName m_name;
};

class NodeNotInNetwork : public std::exception
{
public:
    NodeNotInNetwork(Network* network, Node* node) : m_network(network), m_node(node) {}
    NodeNotInNetwork(const NodeNotInNetwork& other) : m_network(other.m_network), m_node(other.m_node) {}
    virtual ~NodeNotInNetwork() throw () {}
    Network* getNetwork() { return m_network; }
    Node* getNode() { return m_node; }
    NodeNotInNetwork& operator=(const NodeNotInNetwork& other)
    {
        if(this == &other) return *this;
        m_network = other.m_network;
        m_node = other.m_node;
        return *this;
    }
private:
    Network* m_network;
    Node* m_node;
};

typedef std::vector<Node*> NodeList;
typedef NodeList::iterator NodeIterator;

class Network: public Node {
public:
    Network(const ParameterType& outputType = kInt);
    virtual ~Network();
    
    bool isEmpty();
    unsigned int size();
    // Node* create(const NodeLibraryName& libraryName, const NodeName& nodeName);
    std::string setUniqueNodeName(Node* node);
    bool rename(Node* node, const NodeName& name);
    bool add(Node* node); // throws DuplicateName if a node with this name is already in the network.
    bool remove(Node* node);
    // void rename(Node* node, const NodeName& name);
    bool contains(Node* node);
    bool contains(const NodeName& name);
    Node* getNode(const NodeName& name);
    NodeList getNodes();

    Node* getRenderedNode() const;
    void setRenderedNode(Node* node);
            
    friend std::ostream& operator<<(std::ostream& o, const Node& n);
    
protected:
    virtual void process();
    
private:
    // Disallow copy construction or assignment
    Network(const Network& other);
    Network& operator=(const Network& other);

    typedef std::map<NodeName, Node*> NodeMap;
    typedef NodeMap::iterator NodeMapIterator;
    
    NodeMap m_nodes;
    Node* m_renderedNode;
    
    NodeNameMacro(Network);
};

} // namespace NodeCore

#endif // Node_h
