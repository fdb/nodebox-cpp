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
 
#include "NetworkVisualiser.h"

#include <iostream>
using namespace NodeCore;

NetworkVisualiser::NetworkVisualiser()
{
    addField("network", kNetwork);
}

void NetworkVisualiser::process()
{
    const int NODE_WIDTH = 80;
    const int NODE_HEIGHT = 40;
    Canvas c = NodeCore::Canvas(300, 300);
    Network* net = (Network*)asData("network");
    NodeList nodes = net->getNodes();
    for (NodeIterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
        Node* node = (*iter);
        NodeCore::BezierPath p = NodeCore::BezierPath();
        p.rect(node->getX(), node->getY(), NODE_WIDTH, NODE_HEIGHT);
        c.append(p);
    }
    _setOutput(c);
}