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

#ifndef Canvas_h
#define Canvas_h

#include "Grob.h"
#include "BezierPath.h"

#include <iostream>
#include <vector>
#include <ApplicationServices/ApplicationServices.h>

namespace NodeCore {

typedef std::vector<Grob*> GrobList;
typedef std::vector<Grob*>::iterator GrobIterator;

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

    virtual void _draw(CGContextRef ctx);
    void save(std::string fname);

    virtual Canvas* clone() const;

    Canvas& operator=(const Canvas& c);    
    virtual bool operator==(const Grob& g) const;
    virtual bool operator!=(const Grob& g) const { return !operator==(g); }
    Grob* operator[](int n) const;
    friend std::ostream& operator<<(std::ostream& o, const Canvas& c);

private:
    void saveAsPDF(std::string fname);
    GrobList m_grobs;
    float m_width, m_height;
};

} // namespace NodeCore

#endif // Canvas_h
