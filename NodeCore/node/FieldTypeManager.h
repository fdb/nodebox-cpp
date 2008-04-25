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

#ifndef FieldTypeManager_h
#define FieldTypeManager_h

#include "Field.h"

#include <string>
#include <map>
#include <iostream>

namespace NodeCore {

class Field;
class Node;

typedef Field* (*FieldInitializer)(Node *node, FieldName name, FieldPolarity polarity);
typedef std::map<std::string, FieldInitializer> FieldTypeMap;

class FieldTypeNotFound {
public:
    FieldTypeNotFound(FieldType type) : m_type(type) {}
    FieldType getFieldType() { return m_type; }
private:
    FieldType m_type;
};

class FieldTypeManager {
public:

    static void addFieldType(FieldType name, FieldInitializer initializer);
    
    static FieldInitializer getInitializer(FieldType name);
    static Field* initialize(FieldType type, Node *node, FieldName name, FieldPolarity polarity = kIn);
    
private:
    static FieldTypeMap getFieldTypeMap();
};


} // namespace NodeCore

#endif // FieldTypeManager_h
