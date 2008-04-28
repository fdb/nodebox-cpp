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

#ifndef IntField_h
#define IntField_h

#include "Field.h"

#include <string>

namespace NodeCore {

class IntField : public Field {
public:
    IntField(Node *node, FieldName name, FieldPolarity polarity = kIn);
    virtual ~IntField();
    
    virtual int asInt();
    virtual float asFloat();
    virtual std::string asString();
    
    virtual void set(int i);
    virtual void set(float f);
    virtual void set(std::string s);
    
    virtual std::string getTypeName() { return "core/int"; }

protected:
    virtual void revertToDefault();
    virtual void setValueFromConnection();

private:
    // Disallow copy construction or assignment
    IntField(const IntField& other);
    IntField& operator=(const IntField& other);

    int m_value;

    FieldTypeMacro(IntField);
};

} // namespace NodeCore

#endif // IntField_h
