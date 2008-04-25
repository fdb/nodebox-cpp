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

namespace NodeCore {

class Node;

#define FieldTypeMacro(className) \
public: \
    static Field* initialize(Node *node, FieldName name, FieldPolarity polarity = kIn) { \
        return new className(node, name, polarity); \
    }

class ValueError : public std::exception {
public:
    ValueError(std::string message = "") : m_message(message) {}
    virtual ~ValueError() throw () {}
    std::string getMessage() { return m_message; }
private:
    std::string m_message;
};

enum FieldPolarity {
    kIn = 1,
    kOut = 2,
    kInOut = 3
};

class InvalidName : public std::exception {};

typedef std::string FieldName;
typedef std::string FieldType;

const std::string kInt="core/int";
const std::string kFloat="core/float";
const std::string kString="core/string";

typedef std::vector<Connection*> DownstreamList;
typedef DownstreamList::iterator DownstreamIterator;

class Field {
public:
    Field(Node *node, const FieldName& name, FieldPolarity polarity = kIn);
    virtual ~Field();
    
    Node* getNode() const { return m_node; }
    
    virtual int asInt() { return 0; }
    virtual float asFloat() { return 0; }
    virtual std::string Field::asString() { return ""; }

    // All these can throw a ValueError.
    virtual void set(int i) = 0;
    virtual void set(float f) = 0;
    virtual void set(std::string s) = 0;
    
    virtual std::string getTypeName() = 0;
    
    FieldName getName() const { return m_name; }
    FieldPolarity getPolarity() const { return m_polarity; }
    
    static bool validName(const FieldName& name);

    // Connections

    bool isConnected();
    bool isConnectedTo(Field* field);
    Connection* connect(Node *outputNode);
    bool disconnect(Node *outputNode);
    bool disconnect();

    friend std::ostream& operator<<(std::ostream& o, const Field& f);
    
protected:
    virtual void revertToDefault() = 0;
    virtual void setValueFromConnection() = 0;
    void preSet();
    void postSet();
    Connection* getConnection();
    
private:
    void update();
    void markDirty();
    void removeFromDownstreams(Connection* conn);

    Node *m_node;
    std::string m_name;
    std::string m_verboseName;
    bool m_connectable;
    bool m_required;
    bool m_multi;
    FieldPolarity m_polarity;
    Connection *m_connection;
    DownstreamList m_downstreams;
    // TODO: expression
    
    friend class Node;
};

} // namespace NodeCore

#endif // Field_h
