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

typedef std::string ColorMode;
const ColorMode kGray = "Gray";
const ColorMode kRGB = "RGB";
const ColorMode kCMYK = "CMYK";

class Color {
public:
    Color();
    Color(const ColorMode& mode, float v1);
    Color(const ColorMode& mode, float v1, float v2);
    Color(const ColorMode& mode, float v1, float v2, float v3);
    Color(const ColorMode& mode, float v1, float v2, float v3, float v4);
    Color(const ColorMode& mode, float v1, float v2, float v3, float v4, float v5);
    Color(const Color &other);
    virtual ~Color();
    
    static Color grayColor(float gray, float alpha=1.0);
    static Color rgbColor(float red, float green, float blue, float alpha=1.0);
    static Color cmykColor(float cyan, float magenta, float yellow, float black, float alpha=1.0);
    
    CGColorRef _cgColorRef();
    
    virtual Color* clone() const;

    virtual bool operator==(const Color& other) const;
    virtual bool operator!=(const Color& other) const { return !operator==(other); }
};

} // namespace NodeCore
