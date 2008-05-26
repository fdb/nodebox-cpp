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

class PathElement;
class Rect;

class Point {
public:
    Point(float x=0, float y=0) : m_x(x), m_y(y) {}
    Point(const Point &point) : m_x(point.m_x), m_y(point.m_y) {}
    ~Point() {}
    
    float getX() const { return m_x; }
    void setX(float x) { m_x = x; }
    float getY() const { return m_y; }
    void setY(float y) { m_y = y; }

    bool operator==(const Point& p) const;
};

} // namespace NodeCore
