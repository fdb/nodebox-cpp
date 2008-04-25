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

#ifndef PathEement_h
#define PathEement_h

#include "Point.h"

#include <iostream>

namespace NodeCore {

enum PathCommand {
    kMoveto = 0,
    kLineto,
    kCurveto,
    kClose
};

class PathElement {
public:
    PathElement();
    PathElement(PathCommand cmd);
    PathElement(PathCommand cmd, float x, float y);
    PathElement(PathCommand cmd, float x1, float y1, float x2, float y2, float x3, float y3);
    PathElement(const PathElement &path);
    ~PathElement();
    
    PathCommand getCmd() { return m_cmd; }
    float getX() { return m_point.m_x; }
    float getY() { return m_point.m_y; }
    Point getPoint() { return m_point; }
    Point getCtrl1() { return m_ctrl1; }
    Point getCtrl2() { return m_ctrl2; }
    
    PathElement& operator=(const PathElement& pe);
    bool operator==(const PathElement& pe) const;
    friend std::ostream& operator<<(std::ostream& o, const PathElement& p);
    
    friend class BezierPath;

private:
    PathCommand m_cmd;
    Point m_point;
    Point m_ctrl1;
    Point m_ctrl2;
};

} // namespace NodeCore

#endif // PathEement_h
