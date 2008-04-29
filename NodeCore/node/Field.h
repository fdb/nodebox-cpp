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

#ifndef Field_h
#define Field_h

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

typedef std::string FieldName;
typedef std::string FieldType;

const std::string kInt = "int";
const std::string kFloat = "float";
const std::string kString = "string";
const std::string kData = "data";

class Field {
public:
    Field(Node *node, const FieldName& name, const FieldType& type);
    virtual ~Field();
    
    Node* getNode() const { return m_node; }
    
    int asInt();
    float asFloat();
    std::string asString();
    void* asData();

    // All these can throw a ValueError.
    void set(int i);
    void set(float f);
    void set(const std::string& s);
    void set(void* v);
    
    FieldName getName() const { return m_name; }
    FieldType getType() const { return m_type; }
    
    // Connection methods
    Connection* connect(Node* node);
    void disconnect();
    bool isConnected();
    bool isConnectedTo(Node* node);
    Connection* getConnection();
    
    static bool validName(const FieldName& name);

    friend std::ostream& operator<<(std::ostream& o, const Field& f);
    
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
    Field(const Field& other);
    Field& operator=(const Field& other);

    void markDirty();

    Node *m_node;
    std::string m_name;
    std::string m_verboseName;
    FieldType m_type;
    Connection *m_connection;
    Value m_value;
    // TODO: expression
    
    friend class Node;
};

} // namespace NodeCore

#endif // Field_h
