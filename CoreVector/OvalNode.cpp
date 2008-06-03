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
#include "OvalNode.h"

namespace CoreVector {

OvalNode::OvalNode()
        : Node(kCanvas)
{
    addField("x", kFloat);
    addField("y", kFloat);
    addField("width", kFloat);
    addField("height", kFloat);
    set("width", 100.0F);
    set("height", 100.0F);
}

OvalNode::~OvalNode()
{
    if (outputAsData())
        delete (Canvas *)outputAsData();
}

void OvalNode::process()
{
    if (outputAsData())
        delete (Canvas *)outputAsData();
    BezierPath path = BezierPath();
    path.oval(asFloat("x"), asFloat("y"), asFloat("width"), asFloat("height"));
    Canvas *c = new Canvas(200, 200);
    c->append(path);
    _setOutputAsData(c);
}

} // namespace CoreVector
