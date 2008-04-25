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

StringField::StringField(Node *node, FieldName name, FieldPolarity polarity)
            : Field(node, name, polarity)
{
}

StringField::~StringField()
{
}

int StringField::asInt()
{
    return boost::lexical_cast<int>(m_value);
}

float StringField::asFloat()
{
    return boost::lexical_cast<float>(m_value);
}

std::string StringField::asString()
{
    return m_value;
}

void StringField::set(int i)
{
    preSet();
    m_value = boost::lexical_cast<std::string>(i);
    postSet();
}

void StringField::set(float f)
{
    preSet();
    m_value = boost::lexical_cast<std::string>(f);
    postSet();
}

void StringField::set(std::string s)
{
    preSet();
    m_value = s;
    postSet();
}

void StringField::revertToDefault()
{
    m_value = "";
}

void StringField::setValueFromConnection()
{
    assert(isConnected());
    m_value = getConnection()->getOutputField()->asString();
}

} // namespace NodeCore