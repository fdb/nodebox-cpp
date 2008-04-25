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

#include "config.h"
#include "FieldTypeManager.h"

#include "Node.h"
#include "Field.h"
#include "IntField.h"
#include "FloatField.h"
#include "StringField.h"

namespace NodeCore {

void FieldTypeManager::addFieldType(FieldType name, FieldInitializer initializer)
{ 
    getFieldTypeMap()[name] = initializer;
}

FieldInitializer FieldTypeManager::getInitializer(FieldType name) {
    FieldTypeMap ftm = getFieldTypeMap();
    if (ftm.empty()) {
        std::cout << "Initializing the basics." << std::endl;
        // Initialize the basics
        addFieldType("core/int", IntField::initialize);
        addFieldType("core/float", FloatField::initialize);
        addFieldType("core/string", StringField::initialize);
    }
    // TODO: The map size should be 3, but it isn't.
    std::cout << "new map size " << ftm.size() << std::endl;
    return ftm[name];
}

Field* FieldTypeManager::initialize(FieldType type, Node *node, FieldName name, FieldPolarity polarity) {
    FieldInitializer init; //  = getInitializer(type);    
    // TODO: Use the map. The map always remains at size 0 -- why?
    if (type == "core/int") {
        init = IntField::initialize;
    } else if (type == "core/float") {
        init = FloatField::initialize;
    } else if (type == "core/string") {
        init = StringField::initialize;
    } else {
        throw FieldTypeNotFound(type);
    }
    Field* f = (*init)(node, name, polarity);
    return f;
}
    
FieldTypeMap FieldTypeManager::getFieldTypeMap() {
    static FieldTypeMap m_typeMap = FieldTypeMap();
    return m_typeMap;
}

} // namespace NodeCore