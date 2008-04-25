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
#include "FloatField.h"

namespace NodeCore {

FloatField::FloatField(Node *node, FieldName name, FieldPolarity polarity)
        : Field(node, name, polarity), m_value(0)
{
}

FloatField::~FloatField()
{
}

int FloatField::asInt()
{
	// TODO: get rid of boost::lexical_cast
    //return boost::lexical_cast<int>(m_value);
	return (int) m_value;
}

float FloatField::asFloat()
{
    return m_value;
}

std::string FloatField::asString()
{
	// TODO: get rid of boost::lexical_cast
    return ""; // boost::lexical_cast<std::string>(m_value);
}

void FloatField::set(int i)
{
    preSet();
    m_value = (float) i;
    postSet();
}

void FloatField::set(float f)
{
    preSet();
    m_value = f;
    postSet();
}

void FloatField::set(std::string s)
{
    preSet();
	// TODO: get rid of boost::lexical_cast
    // m_value = boost::lexical_cast<float>(s);
    postSet();
}

void FloatField::revertToDefault()
{
    m_value = 0;
}

void FloatField::setValueFromConnection()
{
    assert(isConnected());
    m_value = getConnection()->getOutputField()->asFloat();
}

} // namespace NodeCore