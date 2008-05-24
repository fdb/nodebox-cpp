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
#include "Image.h"

namespace NodeCore {

Image::Image(std::string fname, float x, float y)
     : m_fname(fname), 
       m_x(x), 
       m_y(y),
       m_width(0),
       m_height(0),
       m_image(0)
{
}

Image::Image(const Image& other)
     : m_fname(other.m_fname),
       m_x(other.m_x), 
       m_y(other.m_y),
       m_width(other.m_width),
       m_height(other.m_height),
       m_image(0)
{
}

Image::~Image()
{
    if (m_image == 0) return;
    CGImageRelease(m_image);
}

NodeCore::Rect Image::bounds()
{
    loadImage();
    // TODO: If width and height are implemented, this will change.
    return Rect(m_x, m_y, CGImageGetWidth(m_image), CGImageGetHeight(m_image));
}

Image* Image::clone() const
{
    return new Image(*this);
}

void Image::_draw(CGContextRef ctx)
{
    loadImage();
    // TODO: the image width and height should have been cached already.
    CGRect rect = CGRectMake(0, 0, CGImageGetWidth(m_image), CGImageGetHeight(m_image));
    CGContextSaveGState(ctx);
    CGContextTranslateCTM(ctx, m_x, m_y+CGImageGetHeight(m_image));
    CGContextScaleCTM(ctx, 1, -1);
    CGContextDrawImage(ctx, rect, m_image);
    CGContextRestoreGState(ctx);
}

Image& Image::operator=(const Image& i)
{
    if (this == &i) return *this;
    m_fname = i.m_fname;
    m_x = i.m_x;
    m_y = i.m_y;
    m_width = i.m_width;
    m_height = i.m_height;
    m_image = 0;
    return *this;
}

bool Image::operator==(const Grob& g) const
{
    if (this == &g) return true;
    const Image& i = dynamic_cast<const Image&>(g);
    return m_fname == i.m_fname
        && m_x == i.m_x
        && m_y == i.m_y
        && m_width == i.m_width
        && m_height == i.m_height;
}

std::ostream& operator<<(std::ostream& o, const Image& i)
{
    return o << "Image(" << i.m_fname << ", " << i.m_x << ", " << i.m_y << ")";
}

void Image::loadImage()
{
    if (m_image != NULL) return;
    CFStringRef cfFname = CFStringCreateWithCString(NULL, m_fname.c_str(), kCFStringEncodingUTF8);
    CFURLRef cfUrl = CFURLCreateWithFileSystemPath(NULL, cfFname, kCFURLPOSIXPathStyle, NULL);
    CFRelease(cfFname);
    CGImageSourceRef cgImageSource = CGImageSourceCreateWithURL(cfUrl, NULL);
    CFRelease(cfUrl);
    // TODO: This should be converted to error handling.
    assert(CGImageSourceGetStatus(cgImageSource) == kCGImageStatusComplete);
    assert(CGImageSourceGetCount(cgImageSource) == 1);
    m_image = CGImageSourceCreateImageAtIndex(cgImageSource, 0, NULL);
}

} // namespace NodeCore