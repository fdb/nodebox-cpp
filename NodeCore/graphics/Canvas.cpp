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
#include "Canvas.h"

namespace NodeCore {

Canvas::Canvas(float width, float height)
      : m_grobs(GrobList()),
        m_width(width),
        m_height(height)
      
{
}

Canvas::Canvas(const Canvas& other)
      : m_grobs(GrobList()),
        m_width(other.m_width),
        m_height(other.m_height)
{
    for(unsigned int i=0; i<other.m_grobs.size(); i++) {
        Grob* newGrob = other.m_grobs[i]->clone();
        m_grobs.push_back(newGrob);
    }
}

Canvas::~Canvas()
{
    for (GrobIterator it = m_grobs.begin(); it != m_grobs.end(); ++it) {
        delete (*it);
    }
}

void Canvas::append(const Grob& grob)
{
    Grob* grobCopy = grob.clone();
    m_grobs.push_back(grobCopy);
}

NodeCore::Rect Canvas::bounds()
{
    // TODO: We're running bounds() twice on the first element.
    Rect r = m_grobs[0]->bounds();
    for (GrobIterator it = m_grobs.begin(); it != m_grobs.end(); ++it) {
        r = r.united((*it)->bounds());
    }
    return r;
}

void Canvas::_draw(CGContextRef ctx)
{
    // Flip the canvas
    // TODO: We leave it out here, since it causes confusion with flipped NSViews.
    //CGContextTranslateCTM(ctx, 0, m_height);
    //CGContextScaleCTM(ctx, 1, -1);
    for (GrobIterator it = m_grobs.begin(); it != m_grobs.end(); it++) {
        (*it)->_draw(ctx);
    }
}

void Canvas::save(std::string fname)
{
    saveAsPDF(fname);
}

void Canvas::saveAsPDF(std::string fname)
{
    CGRect rect = CGRectMake(0, 0, m_width, m_height);
    CFStringRef cfFname = CFStringCreateWithCString(NULL, fname.c_str(), kCFStringEncodingUTF8);
    CFURLRef url = CFURLCreateWithFileSystemPath(NULL, cfFname, kCFURLPOSIXPathStyle, 0);
    CFRelease (cfFname);
    CFMutableDictionaryRef info = CFDictionaryCreateMutable(NULL, 0,
                        &kCFTypeDictionaryKeyCallBacks,
                        &kCFTypeDictionaryValueCallBacks);
    // CFDictionarySetValue(info, kCGPDFContextTitle, CFSTR("Test PDF File"));
    CGContextRef pdfContext = CGPDFContextCreateWithURL(url, &rect, info);
    CFRelease(info);
    CFRelease(url);
    CGContextBeginPage(pdfContext, &rect);
    _draw(pdfContext);
    CGContextEndPage(pdfContext);
    CGContextRelease(pdfContext);
}

Canvas& Canvas::operator=(const Canvas& c)
{
    if(this == &c) return *this;
    m_grobs = c.m_grobs;
    m_width = c.m_width;
    m_height = c.m_height;
    return *this;
}

bool Canvas::operator==(const Grob& g) const
{
    if (this == &g) return true;
    const Canvas& c = dynamic_cast<const Canvas&>(g);

    if (m_width != c.m_width || m_height != c.m_height)
        return false;

    if (m_grobs.size() != c.m_grobs.size())
        return false;
    
    for (unsigned int i = 0; i < m_grobs.size(); i++) {
        Grob* g1 = m_grobs[i];
        Grob* g2 = c.m_grobs[i];
        if (*g1 != *g2)
            return false;
    }
    
    return true;
}

Grob* Canvas::operator[](int n) const
{
    return m_grobs[n];
}

std::ostream& operator<<(std::ostream& o, const Canvas& c)
{
    o << "Canvas(" << c.m_width << ", " << c.m_height << ")";
    return o;
}

Canvas* Canvas::clone() const
{
    return new Canvas(*this);
}

} // namespace NodeCore