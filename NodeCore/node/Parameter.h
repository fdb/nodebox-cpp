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

#ifndef Parameter_h
#define Parameter_h

#include "Connection.h"

#include <string>
#include <exception>
#include <iostream>
#include <vector>

namespace NodeCore {

class Node;

class ValueError : public std::exception {
public:
    ValueError(std::string message = "") : m_message(message) {}
    virtual ~ValueError() throw () {}
    std::string getMessage() { return m_message; }
private:
    std::string m_message;
};

class InvalidName : public std::exception {};

typedef std::string ParameterName;
typedef std::string ParameterType;

const ParameterType kInt = "int";
const ParameterType kFloat = "float";
const ParameterType kString = "string";
const ParameterType kNode = "Node";
const ParameterType kNetwork = "Network";

enum ParameterDirection {
    kIn = 1,
    kOut = 2
};

typedef unsigned int Channel;

class Parameter {
public:
    Parameter(Node *node, const ParameterName& name, const ParameterType& type, Channel channels=1, ParameterDirection dir = kIn);
    virtual ~Parameter();
    
    Node* getNode() const { return m_node; }
    ParameterDirection getDirection() const { return m_direction; }
    bool isInputParameter() const { return m_direction == kIn; }
    bool isOutputParameter() const { return m_direction == kOut; }
    Channel channelCount() const { return m_channelCount; }
    
    int asInt(Channel channel=0);
    float asFloat(Channel channel=0);
    std::string asString(Channel channel=0);
    void* asData(Channel channel=0);

    // All these can throw a ValueError.
    void set(int i, Channel channel=0);
    void set(float f, Channel channel=0);
    void set(const std::string& s, Channel channel=0);
    void set(void* v, Channel channel=0);
    
    ParameterName getName() const { return m_name; }
    ParameterType getType() const { return m_type; }
    
    // Connection methods
    bool canConnectTo(Node* node);
    Connection* connect(Node* node);
    bool disconnect();
    bool isConnected();
    bool isConnectedTo(Node* node);
    Connection* getConnection();
    void update();
    
    static bool validName(const ParameterName& name);

    friend std::ostream& operator<<(std::ostream& o, const Parameter& f);
    
protected:
    void revertToDefault();
    void preSet();
    void postSet();
    
private:
    union Value {
        int i;
        float f;
        std::string* s;
        void* d;
    };

    // Disallow copy construction or assignment
    Parameter(const Parameter& other);
    Parameter& operator=(const Parameter& other);

    void markDirty();

    Node *m_node;
    std::string m_name;
    std::string m_verboseName;
    ParameterType m_type;
    ParameterDirection m_direction;
    Connection *m_connection;
    unsigned int m_channelCount;
    Value* m_channels;
    // TODO: expression
    
    friend class Node;
};

} // namespace NodeCore

#endif // Parameter_h
