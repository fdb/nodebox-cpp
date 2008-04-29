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
          : m_output(0)
{
}

CanvasNode::~CanvasNode()
{
    if (m_output) {
        delete m_output;
    }
}

void CanvasNode::setOutput(const Canvas& canvas)
{
    if (m_output) {
        delete m_output;
    }
    m_output = new Canvas(canvas);
}

Canvas CanvasNode::getOutput() const
{
    if (m_output) {
        return *m_output;
    } else {
        return Canvas();
    }
}

void CanvasNode::process()
{
}

void CanvasNode::updateField(Field* f)
{
    assert (f->getType() == kData);
    assert (f->isConnectedTo(this));
    f->set((void*)m_output);
}


} // namespace NodeCore