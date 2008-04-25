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
#include "Point.h"

namespace NodeCore {

Point& Point::operator=(const Point& p)
{
    if (this == &p) return *this;
    m_x = p.m_x;
    m_y = p.m_y;
    return *this;
}

bool Point::operator==(const Point& p) const
{
    return m_x == p.m_x 
        && m_y == p.m_y;
}

std::ostream& operator<<(std::ostream& o, const Point& p)
{
    return o << "[" << p.m_x << "," << p.m_y << "]";
}

} // namespace NodeCore