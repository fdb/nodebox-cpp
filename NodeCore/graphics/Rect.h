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

#ifndef Rect_h
#define Rect_h

#include <iostream>

#include <ApplicationServices/ApplicationServices.h>

namespace NodeCore {

class Rect {
public:
    Rect();
    Rect(float x, float y, float width, float height);
    Rect(CGRect r);
    Rect(const Rect &r);
    
    float getX() { return m_x; }
    float getY() { return m_y; }
    float getWidth() { return m_width; }
    float getHeight() { return m_height; }

    Rect& operator=(const Rect& r);
    bool operator==(const Rect& r) const;
    bool operator!=(const Rect& r) const { return !operator==(r); }
    friend std::ostream& operator<<(std::ostream& o, const Rect& bp);
private:
    float m_x, m_y, m_width, m_height;
};

} // namespace NodeCore

#endif // Rect_h
