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

#include <QtCore/QMap>
#include <QtCore/QObject>

#include "Node.h"
#include "NodeType.h"

namespace NodeCore {

class Network: public Node {
    Q_OBJECT
public:
    Network(NodeType* type, const QString& name=NULL);
    virtual ~Network();
    
    bool isEmpty() const;
    int size() const;
    Node* create(const NodeType* nodeType);
    QString setUniqueNodeName(Node* node);
    bool rename(Node* node, const QString& name);
    bool add(Node* node);
    bool remove(Node* node);
    bool contains(Node* node) const;
    bool contains(const QString& name) const;
    Node* node(const QString& name) const;
    QList<Node*> nodes() const;

    Node* renderedNode() const;
    void setRenderedNode(Node* node);

    bool containsCycles() const;
            
    // friend std::ostream& operator<<(std::ostream& o, const Node& n);
    
protected:
    virtual bool process();
    
private:
    // Disallow copy construction or assignment
    Network(const Network& other);
    Network& operator=(const Network& other);

    QMap<QString, Node*> m_nodes;
    Node* m_renderedNode;
};

} // namespace NodeCore

#endif // Node_h
