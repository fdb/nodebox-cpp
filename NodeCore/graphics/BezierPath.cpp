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
#include "BezierPath.h"

namespace NodeCore {

// Magic number used for drawing bezier circles.
// 4 *(sqrt(2) -1)/3
float const KAPPA = 0.5522847498f;

BezierPath::BezierPath()
          : m_elements(PathElementList()),
            m_fill(true),
            m_fillColor(Color()),
            m_stroke(false),
            m_strokeColor(Color()),
            m_strokeWidth(1.0F),
            m_path(CGPathCreateMutable()),
            m_dirty(true)
{
}

BezierPath::BezierPath(const BezierPath& other)
          : m_elements(other.m_elements),
            m_fill(other.m_fill),
            m_fillColor(other.m_fillColor),
            m_stroke(other.m_stroke),
            m_strokeColor(other.m_strokeColor),
            m_strokeWidth(other.m_strokeWidth),
            m_path(CGPathCreateMutable()),
            m_dirty(true)
{
}

BezierPath::~BezierPath()
{
    CGPathRelease(m_path);
}

void BezierPath::moveto(float x, float y)
{
    m_elements.push_back(PathElement(kMoveto, x, y));
    m_dirty = true;
}

void BezierPath::lineto(float x, float y)
{
    m_elements.push_back(PathElement(kLineto, x, y));
    m_dirty = true;
}

void BezierPath::curveto(float x1, float y1, float x2, float y2, float x3, float y3)
{
    m_elements.push_back(PathElement(kCurveto, x1, y1, x2, y2, x3, y3));
    m_dirty = true;
}

void BezierPath::close()
{
    m_elements.push_back(PathElement(kClose));
    m_dirty = true;
}

void BezierPath::rect(float x, float y, float width, float height)
{
    moveto(x, y);
    lineto(x + width, y);
    lineto(x+ width, y + height);
    lineto(x, y + height);
    close();
}

void BezierPath::roundedRect(float x, float y, float width, float height, float roundness)
{
    float cv = width < height ? width*roundness : height*roundness;
    moveto(x, y+cv);
    curveto(x, y, x, y, x+cv, y);
    lineto(x+width-cv, y);
    curveto(x+width, y+height, x+width, y+height, x+width-cv, y+height);
    lineto(x+cv, y+height);
    curveto(x, y+height, x, y+height, x, y+height-cv);
    close();
}

void BezierPath::oval(float x, float y, float width, float height)
{
    float hdiff = width / 2 * KAPPA;
    float vdiff = height / 2 * KAPPA;
    moveto(x + width / 2, y + height);
    curveto(x + width / 2 - hdiff, y + height,
            x, y + height / 2 + vdiff,
            x, y + height / 2);
    curveto(x, y + height / 2 - vdiff,
            x + width / 2 - hdiff, y,
            x + width / 2, y);
    curveto(x + width / 2 + hdiff , y,
            x+width,  y + height / 2 - vdiff,
            x+width, y + height / 2);
    curveto(x + width, y + height / 2 + vdiff,
            x + width / 2 + hdiff, y + height,
            x + width / 2, y + height);
}

void BezierPath::line(float x1, float y1, float x2, float y2)
{
    moveto(x1, y1);
    lineto(x2, y2);
}

void BezierPath::clear()
{
    m_elements.clear();
}

unsigned int BezierPath::size()
{
    return m_elements.size();
}

bool BezierPath::isempty()
{
    return m_elements.empty();
}

void BezierPath::append(const PathElement& el)
{
    m_elements.push_back(el);
}

NodeCore::Rect BezierPath::bounds()
{
    CGRect r = CGPathGetBoundingBox(cgPath());
    return Rect(r);
}

Color BezierPath::fillColor()
{
    return m_fillColor;
}

void BezierPath::setFillColor(const Color& c)
{
    m_fill = true;
    m_fillColor = c;
}

void BezierPath::noFill()
{
    m_fill = false;
}

Color BezierPath::strokeColor()
{
    return m_strokeColor;
}

void BezierPath::setStrokeColor(const Color& c)
{
    m_stroke = true;
    m_strokeColor = c;
}

void BezierPath::noStroke()
{
    m_stroke = false;
}

float BezierPath::strokeWidth()
{
    return m_strokeWidth;
}

void BezierPath::setStrokeWidth(float width)
{
    m_strokeWidth = width;
}

CGMutablePathRef BezierPath::cgPath()
{    
    if (!m_dirty) return m_path;
    CGMutablePathRef p = CGPathCreateMutable();
    Point c1, c2;
    for (PathElementIterator iter=m_elements.begin(); iter != m_elements.end(); iter++) {
        PathElement el = (*iter);
        switch (el.m_cmd) {
            case kMoveto:
                CGPathMoveToPoint(p, 0, el.getX(), el.getY());
                break;
            case kLineto:
                CGPathAddLineToPoint(p, 0, el.getX(), el.getY());
                break;
            case kCurveto:
                c1 = el.getCtrl1();
                c2 = el.getCtrl2();
                CGPathAddCurveToPoint(p, 0, el.getX(), el.getY(), c1.getX(), c1.getY(), c2.getX(), c2.getY());
                break;
            case kClose:
                CGPathCloseSubpath(p);
                break;
            default:
                assert(false);
        }
    }
    CGPathRelease(m_path);
    m_path = p;
    m_dirty = false;
    return m_path;
}

void BezierPath::transform(const Transform& t)
{
    // Has to be done by my own functions
    // Maybe use applier to extract path element data from cgpath?
//    CGMutablePathRef path = CGPathCreateMutable();
//    CGAffineTransform t = transform;
//    CGPathAddPath(path, &t, m_path);
//    CGPathRelease(m_path);
//    m_path = path;
}

void BezierPath::_draw(CGContextRef ctx)
{
    if (m_fill) {
        CGContextSetFillColorWithColor(ctx, m_fillColor._cgColorRef());
    }
    if (m_stroke) {
        CGContextSetStrokeColorWithColor(ctx, m_strokeColor._cgColorRef());
        CGContextSetLineWidth(ctx, m_strokeWidth);
    }
    CGPathDrawingMode mode;
    if (m_fill && m_stroke) {
        mode = kCGPathFillStroke;
    } else if (m_fill) {
        mode = kCGPathFill;
    } else if (m_stroke) {
        mode = kCGPathStroke;
    } else {
        return;
    }
    CGContextBeginPath(ctx);
    CGContextAddPath(ctx, cgPath());
    CGContextDrawPath(ctx, mode);
}

bool BezierPath::operator==(const Grob& g) const
{
    if (this == &g) return true;
    const BezierPath& bp = dynamic_cast<const BezierPath&>(g);
    return m_elements == bp.m_elements;    
}

BezierPath& BezierPath::operator=(const BezierPath& bp)
{
    if (this == &bp) return *this;
    m_elements = bp.m_elements;
    m_fill = bp.m_fill;
    m_fillColor = bp.m_fillColor;
    m_stroke = bp.m_stroke;
    m_strokeColor = bp.m_strokeColor;
    m_strokeWidth = bp.m_strokeWidth;
    m_dirty = true;
    return *this;
}

PathElement BezierPath::operator[](int n) const
{
    return m_elements[n];
}

std::ostream& operator<<(std::ostream& o, const BezierPath& bp)
{
    o << "BezierPath(";
    for (unsigned int i=0; i < bp.m_elements.size(); i++) {
        o << bp.m_elements[i] << ",";
    }
    /*
    for (PathElementIterator iter=bp.m_elements.begin(); iter != bp.m_elements.end(); ++iter) {
        o << (*iter) << ",";
    }
    */
    o << ")";
    return o;
}

BezierPath* BezierPath::clone() const
{
    return new BezierPath(*this);
}

} // namespace NodeCore