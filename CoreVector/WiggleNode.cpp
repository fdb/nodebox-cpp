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

#include <stdio.h> // for rand() and srand()

#include "CoreVector.h"
#include "WiggleNode.h"

float randomize(float v, float amount) {
    float r = ((float)(rand() % 100000)) / 100000.0f;
    return v + amount * r;
}

namespace CoreVector {

WiggleNode::WiggleNode()
        : Node(kCanvas)
{
    addParameter("canvas", kCanvas);
    addParameter("wx", kFloat);
    addParameter("wy", kFloat);
    addParameter("seed", kFloat);
}

WiggleNode::~WiggleNode()
{
    if (outputAsData())
        delete (Canvas *)outputAsData();
}

void WiggleNode::process()
{
    if (outputAsData())
        delete (Canvas *)outputAsData();
    float wx = asFloat("wx");
    float wy = asFloat("wy");
    float seed = asFloat("seed");
    srand( (int) seed * 100 );
    Canvas *in = (Canvas *) asData("canvas");
    Canvas *c = new Canvas(200, 200);
    if (in) {
        GrobList grobs = in->grobs();
        for (GrobIterator grobIter = grobs.begin(); grobIter != grobs.end(); ++grobIter) {
            // TODO: unsafe cast; this is not always a BezierPath. Perhaps implement some RTTI?
            BezierPath *inPath = (BezierPath*)(*grobIter);
            BezierPath *outPath = new BezierPath();
            PathElementList elements = inPath->elements();
            for (PathElementIterator elementIter = elements.begin(); elementIter != elements.end(); ++elementIter) {
                PathElement inElement = (PathElement)(*elementIter);
                PathElement outElement;
                switch (inElement.getCmd()) {
                    case kMoveto:
                    case kLineto:
                        outElement = PathElement(inElement.getCmd(), randomize(inElement.getX(), wx), randomize(inElement.getY(), wy));
                        break;
                    case kCurveto:
                        outElement = PathElement(inElement.getCmd(), randomize(inElement.getX(), wx), randomize(inElement.getY(), wy), randomize(inElement.getCtrl1().getX(), wx), randomize(inElement.getCtrl1().getY(), wy), randomize(inElement.getCtrl2().getX(), wx), randomize(inElement.getCtrl2().getY(), wx));
                        break;
                    case kClose:
                        outElement = PathElement(inElement.getCmd());
                        break;
                }
                outPath->append(outElement);   
            }
            c->append(*outPath);
        }
    }
    _setOutputAsData(c);
}

} // namespace CoreVector
