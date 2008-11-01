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

namespace NodeCore {

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
    
protected:
    virtual void process();
};

} // namespace NodeCore
