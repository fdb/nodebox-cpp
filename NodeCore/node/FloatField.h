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

#ifndef FloatField_h
#define FloatField_h

#include <string>

#include "Field.h"

namespace NodeCore {

class FloatField : public Field {
public:
    FloatField(Node *node, FieldName name, FieldPolarity polarity = kIn);
    virtual ~FloatField();

    virtual int asInt();
    virtual float asFloat();
    virtual std::string asString();
    
    virtual void set(int i);
    virtual void set(float f);
    virtual void set(std::string s);

    virtual std::string getTypeName() { return "core/float"; }

protected:
    virtual void revertToDefault();
    virtual void setValueFromConnection();

private:
    float m_value;

    FieldTypeMacro(FloatField);
};

} // namespace NodeCore

#endif // FloatField_h
