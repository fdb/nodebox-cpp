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

#include "Parameter.h"

#include <string>
#include <exception>
#include <iostream>
#include <map>

namespace NodeCore {

typedef std::map<std::string, Parameter*> ParameterMap;
typedef ParameterMap::iterator ParameterMapIterator;

#define NodeNameMacro(nodeName) \
public: \
    static Node* initialize() { return new nodeName(); } \
    virtual std::string className() const { return #nodeName; }

typedef std::string NodeName;
typedef std::string NodeType;

class ParameterNotFound : public std::exception
{
public:
    ParameterNotFound(const ParameterName& name) : m_name(name) {}
    virtual ~ParameterNotFound() throw () {}
    ParameterName getName() { return m_name; }
private:
    ParameterName m_name;
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

typedef std::vector<Parameter*> ParameterList;
typedef ParameterList::iterator ParameterIterator;
typedef std::vector<Connection*> ConnectionList;
typedef ConnectionList::iterator ConnectionIterator;

class Node {
public:
    Node(const ParameterType& outputType = kInt);
    virtual ~Node();
    
    virtual NodeName defaultName() const;
    
    NodeName getName() const;
    void setName(const NodeName &name);
    static bool validName(const NodeName& name);
    
    void setNetwork(Network* network);
    Network* getNetwork();
        
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    void setX(float x);
    void setY(float y);

    Parameter* addParameter(const ParameterName &name, const ParameterType& type);
    Parameter* getParameter(const ParameterName &name) const;
    bool hasParameter(const ParameterName &name) const;
    Parameter* getOutputParameter() const { return m_outputParameter; }
    ParameterType getOutputType() const { return m_outputParameter->getType(); }
    ParameterList getParameters();
    
    // Value shortcuts
    int asInt(const ParameterName &name);
    float asFloat(const ParameterName &name);
    std::string asString(const ParameterName &name);
    void* asData(const ParameterName &name);
    
    // All these can throw a ValueError.
    void set(const ParameterName &name, int i);
    void set(const ParameterName &name, float f);
    void set(const ParameterName &name, const std::string& s);
    void set(const ParameterName &name, void* d);
    
    void update();
    bool isDirty() const;
    void markDirty();
    
    bool isOutputConnected();
    bool isOutputConnectedTo(Node* node);
    bool isOutputConnectedTo(Parameter* parameter);
    ConnectionList getOutputConnections();

    int outputAsInt() const;
    float outputAsFloat() const;
    std::string outputAsString() const;
    void* outputAsData() const;

    void _setOutput(int i);
    void _setOutput(float f);
    void _setOutput(std::string s);
    void _setOutput(void* d);
    // Needed for setOutput overrides
    void _setOutputAsData(void* d) { _setOutput(d); }

    friend std::ostream& operator<<(std::ostream& o, const Node& n);
    
protected:
    virtual void process();
    
private:
    // Disallow copy construction or assignment
    Node(const Node& other);
    Node& operator=(const Node& other);
    
    void Node::_setName(const NodeName& name);

    void addDownstream(Connection* c);
    void removeDownstream(Connection* c);
    
    float m_x, m_y;
    std::string m_name;
    Network* m_network;
    ParameterMap m_parameters;
    Parameter* m_outputParameter;
    ConnectionList m_downstreams;
    // TODO: add exception
    bool m_dirty;

    NodeNameMacro(Node);
    
    friend class Parameter;
    friend class Network;
};

} // namespace NodeCore

#endif // Node_h
