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

class Transform;
class PathElement;

class BezierPath : public Grob {
public:
    BezierPath();
    BezierPath(const BezierPath &path);
    virtual ~BezierPath();
    
    void moveto(float x, float y);
    void lineto(float x, float y);
    void curveto(float x1, float y1, float x2, float y2, float x3, float y3);
    void close();
    
    void rect(float x, float y, float width, float height);
    void roundedRect(float x, float y, float width, float height, float roundness);
    void oval(float x, float y, float width, float height);
    void line(float x1, float y1, float x2, float y2);
    
    void clear();
    unsigned int size();
    bool isempty();
    virtual NodeCore::Rect bounds();
    
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

    virtual bool operator==(const Grob& g) const;
    virtual bool operator!=(const Grob& g) const { return !operator==(g); }
};

} // namespace NodeCore
