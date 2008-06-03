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

const float DEFAULT_WIDTH = 1000;
const float DEFAULT_HEIGHT = 1000;

class Canvas : public Grob {
public:
    Canvas(float width=DEFAULT_WIDTH, float height=DEFAULT_HEIGHT);
    Canvas(const Canvas &other);
    virtual ~Canvas();
    
    void append(const Grob& grob);
    unsigned int size() { return m_grobs.size(); };
    void clear() { m_grobs.clear(); };

    virtual NodeCore::Rect bounds();

    virtual void _draw(CGContextRef ctx);
    void save(std::string fname);

    virtual Canvas* clone() const;

    virtual bool operator==(const Grob& g) const;
    virtual bool operator!=(const Grob& g) const { return !operator==(g); }
};

} // namespace NodeCore
