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

#ifndef BezierPath_h
#define BezierPath_h

#include "Rect.h"
#include "Grob.h"
#include "PathElement.h"
#include "Color.h"

#include <iostream>
#include <vector>
#include <ApplicationServices/ApplicationServices.h>

namespace NodeCore {

class Transform;
class PathElement;

typedef std::vector<PathElement> PathElementList;
typedef PathElementList::iterator PathElementIterator;

class BezierPath : public Grob {
public:
    BezierPath();
    BezierPath(const BezierPath &path);
    virtual ~BezierPath();
    
    //// Path methods ////
    
    void moveto(float x, float y);
    void lineto(float x, float y);
    void curveto(float x1, float y1, float x2, float y2, float x3, float y3);
    void close();
    
    //// Basic shapes ////

    void rect(float x, float y, float width, float height);
    void roundedRect(float x, float y, float width, float height, float roundness);
    void oval(float x, float y, float width, float height);
    void line(float x1, float y1, float x2, float y2);
    
    //// List operations ////
    
    PathElementList elements() const { return m_elements; }
    PathElement operator[](int n) const;
    void clear();
    unsigned int size() const;
    bool isempty() const;
    void append(const PathElement& el);
    
    //// Geometry ////

    virtual NodeCore::Rect bounds(); 
    
    //// Color ////
    
    Color fillColor();
    void setFillColor(const Color& c);
    void noFill();
    Color strokeColor();
    void setStrokeColor(const Color& c);
    void noStroke();
    float strokeWidth();
    void setStrokeWidth(float width);
    
    CGMutablePathRef cgPath();
    void transform(const Transform& t);

    virtual void _draw(CGContextRef ctx);
    
    virtual BezierPath* clone() const;

    BezierPath& operator=(const BezierPath& bp);
    virtual bool operator==(const Grob& g) const;
    virtual bool operator!=(const Grob& g) const { return !operator==(g); }
    friend std::ostream& operator<<(std::ostream& o, const BezierPath& bp);

private:
    PathElementList m_elements;
    bool m_fill;
    Color m_fillColor;
    bool m_stroke;
    Color m_strokeColor;
    float m_strokeWidth;
    CGMutablePathRef m_path; // transient
    bool m_dirty; // transient
};

} // namespace NodeCore

#endif // BezierPath_h
