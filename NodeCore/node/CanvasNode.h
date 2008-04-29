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

#ifndef CanvasNode_h
#define CanvasNode_h

#include "Node.h"
#include "Canvas.h"

#include <string>
#include <exception>

namespace NodeCore {

class CanvasNode : public Node
{
public:
    CanvasNode();
    virtual ~CanvasNode();
    
    Canvas getOutput() const;
    
protected:
    virtual void process();
    void setOutput(const Canvas& c);
    virtual void updateField(Field* f);

private:
    // Disallow copy construction or assignment
    CanvasNode(const CanvasNode& other);
    CanvasNode& operator=(const CanvasNode& other);

    Canvas* m_output;
};

} // namespace NodeCore

#endif // CanvasNode_h