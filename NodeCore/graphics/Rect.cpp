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
#include "Rect.h"
#include <math.h>

namespace NodeCore {

Rect::Rect()
    : m_x(0),
      m_y(0),
      m_width(0),
      m_height(0)
{
}

Rect::Rect(float x, float y, float width, float height)
    : m_x(x),
      m_y(y),
      m_width(width),
      m_height(height)
{
}

Rect::Rect(CGRect r)
    : m_x(r.origin.x),
      m_y(r.origin.y),
      m_width(r.size.width),
      m_height(r.size.height)
{
}

Rect::Rect(const Rect &r)
     : m_x(r.m_x),
       m_y(r.m_y),
       m_width(r.m_width),
       m_height(r.m_height)
{
}

bool Rect::isEmpty() const
{
    Rect n = normalized();
    return n.m_width <= 0.0F || n.m_height <= 0.0F;
}

Rect Rect::normalized() const
{
    Rect r = *this;
    if (r.m_width < 0) {
        r.m_x += r.m_width;
        r.m_width = -r.m_width;
    }
    if (r.m_height < 0) {
        r.m_y += r.m_height;
        r.m_height = -r.m_height;
    }
    return r;
}

Rect Rect::united(const Rect &r) const
{
    Rect r1 = normalized();
    Rect r2 = r.normalized();
    Rect u;
    u.m_x = fminf(r1.m_x, r2.m_x);
    u.m_y = fminf(r1.m_y, r2.m_y);
    u.m_width = fmaxf(r1.m_x + r1.m_width, r2.m_x + r2.m_width) - u.m_x;
    u.m_height = fmaxf(r1.m_y + r1.m_height, r2.m_y + r2.m_height) - u.m_y;
    return u;
}

Rect& Rect::operator=(const Rect& r)
{
    if (this == &r) return *this;
    m_x = r.m_x;
    m_y = r.m_y;
    m_width = r.m_width;
    m_height = r.m_height;
    return *this;
}

bool Rect::operator==(const Rect& r) const
{
    return m_x == r.m_x
        && m_y == r.m_y
        && m_width == r.m_width
        && m_height == r.m_height;
}

std::ostream& operator<<(std::ostream& o, const Rect& r)
{
    o << "Rect(" << r.m_x << ", " << r.m_y << ", " << r.m_width << ", " << r.m_height << ")";
    return o;
}

} // namespace NodeCore