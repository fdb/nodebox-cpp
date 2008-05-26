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
    float getX() { return m_point.getX(); }
    float getY() { return m_point.getY(); }
    NodeCore::Point getPoint() { return m_point; }
    NodeCore::Point getCtrl1() { return m_ctrl1; }
    NodeCore::Point getCtrl2() { return m_ctrl2; }
    
    bool operator==(const PathElement& pe) const;
    
    friend class BezierPath;
};

} // namespace NodeCore
