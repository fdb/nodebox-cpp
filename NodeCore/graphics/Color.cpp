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
#include "Color.h"

namespace NodeCore {

Color::Color()
     : m_color(CGColorCreateGenericGray(0.0F, 1.0F))
{
}

Color::Color(float v1)
     : m_color(CGColorCreateGenericGray(v1, 1.0F))
{
}

Color::Color(float v1, float v2)
     : m_color(CGColorCreateGenericGray(v1, v2))
{
}

Color::Color(const Color& other)
     : m_color(CGColorCreateCopy(other.m_color))
{
}

Color::~Color()
{
    CGColorRelease(m_color);
}

CGColorRef Color::_cgColorRef()
{
    return m_color;
}

bool Color::operator==(const Color& other) const
{
    if (this == &other) return true;
    return CGColorEqualToColor(m_color, other.m_color);
}

Color& Color::operator=(const Color& other)
{
    if (this == &other) return *this;
    CGColorRelease(m_color);
    m_color = CGColorCreateCopy(other.m_color);
    return *this;
}

std::ostream& operator<<(std::ostream& o, const Color& c)
{
    o << "Color(";
    
    int numComponents = CGColorGetNumberOfComponents(c.m_color);
    const CGFloat* components=CGColorGetComponents(c.m_color);
    
    for (int i=0; i < numComponents; i++) {
        o << components[i];
        if (i != numComponents-1) o << ",";
    }
    o << ")";
    return o;
}

Color* Color::clone() const
{
    return new Color(*this);
}

} // namespace NodeCore