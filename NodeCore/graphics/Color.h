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

#ifndef Color_h
#define Color_h

#include <iostream>
#include <ApplicationServices/ApplicationServices.h>

namespace NodeCore {

class Color {
public:
    Color();
    Color(float v1);
    Color(float v1, float v2);
    Color(const Color &other);
    virtual ~Color();
    
    // virtual void _set(CGContextRef ctx);
    CGColorRef _cgColorRef();
    
    virtual Color* clone() const;

    Color& operator=(const Color& other);
    virtual bool operator==(const Color& other) const;
    virtual bool operator!=(const Color& other) const { return !operator==(other); }
    friend std::ostream& operator<<(std::ostream& o, const Color& c);

private:
    CGColorRef m_color;
};

} // namespace NodeCore

#endif // Color_h
