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
    static Node* initialize() { return new nodeName; } \
    virtual std::string className() { return #nodeName; }

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

// TODO: forbidden names

class Node {
public:
    Node();
    virtual ~Node();
    
    virtual NodeName defaultName() { return className(); };

    Field* addField(const FieldName &name, FieldType type, FieldPolarity polarity=kIn);
    Field* getField(const FieldName &name);
    bool hasField(const FieldName &name);
    Field* getOutputField();
    
    // Value shortcuts
    int asInt(const FieldName &name);
    float asFloat(const FieldName &name);
    std::string asString(const FieldName &name);

    // All these can throw a ValueError.
    void set(const FieldName &name, int i);
    void set(const FieldName &name, float f);
    void set(const FieldName &name, std::string s);
    
    NodeName getName();
    void setName(const NodeName &name);
    static bool validName(const NodeName& name);
    
    
    void update();
    bool isDirty();
    void markDirty();

    friend std::ostream& operator<<(std::ostream& o, const Node& n);
    
protected:
    virtual void process();
    
private:
    // Disallow copy construction or assignment
    Node(const Node& other);
    Node& operator=(const Node& other);

    float m_x, m_y;
    std::string m_name;
    FieldMap m_fields;
    // TODO: add exception
    bool m_dirty;

    NodeNameMacro(Node);
};

} // namespace NodeCore

#endif // Node_h
