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

#include <boost/lexical_cast.hpp>

#include "NodeCore.h"

namespace NodeCore {

IntField::IntField(Node *node, FieldName name, FieldPolarity polarity)
        : Field(node, name, polarity), m_value(0)
{
}

IntField::~IntField()
{
}

int IntField::asInt()
{
    return m_value;
}

float IntField::asFloat()
{
    return boost::lexical_cast<float>(m_value);
}

std::string IntField::asString()
{
    return boost::lexical_cast<std::string>(m_value);
}

void IntField::set(int i)
{
    preSet();
    m_value = i;
    postSet();
}

void IntField::set(float f)
{
    preSet();
    m_value = (int) f;
    postSet();
}

void IntField::set(std::string s)
{
    preSet();
    m_value = boost::lexical_cast<int>(s);
    postSet();
}

void IntField::revertToDefault()
{
    m_value = 0;
}

void IntField::setValueFromConnection()
{
    assert(isConnected());
    m_value = getConnection()->getOutputField()->asInt();
}

} // namespace NodeCore