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

#ifndef Point_h
#define Point_h

#include <iostream>

namespace NodeCore {

class PathElement;

class Point {
public:
    Point(float x=0, float y=0) : m_x(x), m_y(y) {}
    Point(const Point &point) : m_x(point.m_x), m_y(point.m_y) {}
    ~Point() {}
    
    float getX() { return m_x; }
    void setX(float x) { m_x = x; }
    float getY() { return m_y; }
    void setY(float y) { m_y = y; }
    
    Point& operator=(const Point& p);
    bool operator==(const Point& p) const;
    friend std::ostream& operator<<(std::ostream& o, const Point& p);
    friend std::ostream& operator<<(std::ostream& o, const PathElement& p);

    friend class PathElement;

private:
    float m_x;
    float m_y;
};

} // namespace NodeCore

#endif // Point_h
