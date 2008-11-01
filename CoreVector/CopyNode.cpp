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

#include "CoreVector.h"
#include "CopyNode.h"

namespace CoreVector {

CopyNode::CopyNode()
        : Node(kCanvas)
{
    addParameter("canvas", kCanvas);
    // TODO: copies should become an integer parameter
    addParameter("copies", kFloat);
    addParameter("tx", kFloat);
    addParameter("ty", kFloat);
    addParameter("sx", kFloat);
    addParameter("sy", kFloat);
    addParameter("r", kFloat);
    set("copies", 1.0F);
    set("sx", 1.0F);
    set("sy", 1.0F);
}

CopyNode::~CopyNode()
{
    if (outputAsData())
        delete (Canvas *)outputAsData();
}

void CopyNode::process()
{
    if (outputAsData())
        delete (Canvas *)outputAsData();
    Canvas *in = (Canvas *) asData("canvas");
    Canvas *c = new Canvas(200, 200);    
    if (in) {
        c->append(*in->clone());
    }
    BezierPath path = BezierPath();
    path.rect(100, 100, 50, 10);
    c->append(path);
    _setOutputAsData(c);
}

} // namespace CoreVector
