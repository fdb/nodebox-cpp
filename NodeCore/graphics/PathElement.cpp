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
#include "PathElement.h"

#include "Exceptions.h"

namespace NodeCore {

PathElement::PathElement()
           : m_cmd(kClose), 
             m_point(Point(0, 0)),
             m_ctrl1(Point(0, 0)),
             m_ctrl2(Point(0, 0))
{
}

PathElement::PathElement(PathCommand cmd)
            : m_cmd(cmd),
             m_point(Point(0, 0)),
             m_ctrl1(Point(0, 0)),
             m_ctrl2(Point(0, 0))
{
    if (cmd != kClose) {
        throw NodeBoxError("PathElement without coordinates can only be CLOSE.");
    }
}

PathElement::PathElement(PathCommand cmd, float x, float y)
            : m_cmd(cmd),
              m_point(Point(x, y)),
              m_ctrl1(Point(0, 0)),
              m_ctrl2(Point(0, 0))
{
    if (cmd != kMoveto && cmd != kLineto) {
        throw NodeBoxError("PathElement with 1 coordinate can only be MOVETO or LINETO.");
    }
}

PathElement::PathElement(PathCommand cmd, float x1, float y1, float x2, float y2, float x3, float y3)
            : m_cmd(cmd),
             m_point(Point(x1, y1)),
             m_ctrl1(Point(x2, y2)),
             m_ctrl2(Point(x3, y3))
{
    if (cmd != kCurveto) {
        throw NodeBoxError("PathElement with 3 coordinates can only be CURVETO.");
    }
}

PathElement::PathElement(const PathElement &path)
           : m_cmd(path.m_cmd),
             m_point(path.m_point),
             m_ctrl1(path.m_ctrl1),
             m_ctrl2(path.m_ctrl2)
{
}

PathElement::~PathElement()
{
}

PathElement& PathElement::operator=(const PathElement& pe)
{
    if (this == &pe) return *this;
    m_cmd = pe.m_cmd;
    m_point = pe.m_point;
    m_ctrl1 = pe.m_ctrl1;
    m_ctrl2 = pe.m_ctrl2;
    return *this;
}

bool PathElement::operator==(const PathElement& pe) const
{
    return m_cmd == pe.m_cmd
        && m_point == pe.m_point
        && m_ctrl1 == pe.m_ctrl1
        && m_ctrl2 == pe.m_ctrl2;
}

std::ostream& operator<<(std::ostream& o, const PathElement& p)
{
    switch (p.m_cmd) {
        case kMoveto:
            return o << "PathElement(MOVETO, " << p.m_point.m_x << ", " << p.m_point.m_y << ")";
        case kLineto:
            return o << "PathElement(LINETO, " << p.m_point.m_x << ", " << p.m_point.m_y << ")";
        case kCurveto:
            return o << "PathElement(CURVETO, " << p.m_point.m_x << ", " << p.m_point.m_y << "," 
                                                << p.m_ctrl1.m_x << ", " << p.m_ctrl1.m_y << "," 
                                                << p.m_ctrl2.m_x << ", " << p.m_ctrl2.m_y << ")";
        case kClose:
            return o << "PathElement(CLOSE)";
        default: assert(false);
    }
}

} // namespace NodeCore