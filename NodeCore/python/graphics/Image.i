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

class Image : public Grob {
public:
    Image(std::string fname, float x, float y);
    Image(const Image &other);
    virtual ~Image();
    
    virtual NodeCore::Rect bounds();
    virtual void _draw(CGContextRef ctx);

    virtual Image* clone() const;

    virtual bool operator==(const Grob& i) const;
    virtual bool operator!=(const Grob& i) const { return !operator==(i); }
};

} // namespace NodeCore