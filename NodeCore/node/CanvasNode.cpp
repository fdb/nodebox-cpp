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
#include "CanvasNode.h"

namespace NodeCore {

CanvasNode::CanvasNode()
          : Node(kCanvas)
{
}

CanvasNode::~CanvasNode()
{
    if (outputAsData()) {
        delete (Canvas*)outputAsData();
    }
}


void CanvasNode::process()
{
}

Canvas CanvasNode::outputAsCanvas() const {
    if (outputAsData()) {
        return *((Canvas*)outputAsData());
    } else {
        return Canvas();
    }
}

void CanvasNode::setOutput(const Canvas& c)
{
    Canvas* myCanvas = new Canvas(c);
    setOutputAsData((void*)myCanvas);
}

} // namespace NodeCore