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

#ifndef Node_h
#define Node_h

#include "Field.h"

#include <string>
#include <exception>
#include <iostream>
#include <map>

namespace NodeCore {

typedef std::map<std::string, Field*> FieldMap;
typedef FieldMap::iterator FieldIterator;

#define NodeNameMacro(nodeName) \
public: \
    static Node* initialize() { return new nodeName(); } \
    virtual std::string className() const { return #nodeName; }

typedef std::string NodeName;
typedef std::string NodeType;

class FieldNotFound : public std::exception
{
public:
    FieldNotFound(const FieldName& name) : m_name(name) {}
    virtual ~FieldNotFound() throw () {}
    FieldName getName() { return m_name; }
private:
    FieldName m_name;
};

class NodeProcessingError : public std::exception
{
public:
    NodeProcessingError(Node* node, const std::string& msg="")
            : m_node(node), m_message(msg) {}
    NodeProcessingError(const NodeProcessingError& other)
            : m_node(other.m_node), m_message(other.m_message) {}
    virtual ~NodeProcessingError() throw() {}
    Node* getNode() { return m_node; }
    std::string getMessage() { return m_message; }
    NodeProcessingError& operator=(const NodeProcessingError& other)
    {
        if(this == &other) return *this;
        m_node = other.m_node;
        m_message = other.m_message;
        return *this;
    }
private:
    Node* m_node;
    std::string m_message;
};

class Network;

class Node {
public:
    Node(const FieldType& outputType = kInt);
    virtual ~Node();
    
    virtual NodeName defaultName() const { return className(); };
    
    NodeName getName() const;
    void setName(const NodeName &name);
    static bool validName(const NodeName& name);
    
    void setNetwork(Network* network);
    Network* getNetwork();

    Field* addField(const FieldName &name, const FieldType& type);
    Field* getField(const FieldName &name) const;
    bool hasField(const FieldName &name) const;
    Field* getOutputField() const { return m_outputField; }
    FieldType getOutputType() const { return m_outputField->getType(); }
    
    // Value shortcuts
    int asInt(const FieldName &name);
    float asFloat(const FieldName &name);
    std::string asString(const FieldName &name);
    void* asData(const FieldName &name);
    
    int outputAsInt() const;
    float outputAsFloat() const;
    std::string outputAsString() const;
    void* outputAsData() const;

    // All these can throw a ValueError.
    void set(const FieldName &name, int i);
    void set(const FieldName &name, float f);
    void set(const FieldName &name, const std::string& s);
    void set(const FieldName &name, void* d);
    
    void update();
    bool isDirty() const;
    void markDirty();
    
    bool isOutputConnected();
    bool isOutputConnectedTo(Node* node);
    bool isOutputConnectedTo(Field* field);

    friend std::ostream& operator<<(std::ostream& o, const Node& n);
    
protected:
    virtual void process();
    void setOutput(int i);
    void setOutput(float f);
    void setOutput(std::string s);
    void setOutput(void* d);
    // Needed for setOutput overrides
    void setOutputAsData(void* d) { setOutput(d); }
    
private:
    // Disallow copy construction or assignment
    Node(const Node& other);
    Node& operator=(const Node& other);
    
    void addDownstream(Connection* c);
    void removeDownstream(Connection* c);
    typedef std::vector<Connection*> ConnectionList;
    typedef ConnectionList::iterator ConnectionIterator;
    
    float m_x, m_y;
    std::string m_name;
    Network* m_network;
    FieldMap m_fields;
    Field* m_outputField;
    ConnectionList m_downstreams;
    // TODO: add exception
    bool m_dirty;

    NodeNameMacro(Node);
    
    friend class Field;
    friend class Network;
};

} // namespace NodeCore

#endif // Node_h
