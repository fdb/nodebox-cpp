/*
 *  NetworkVisualiser.cpp
 *  NodeBox
 *
 *  Created by Frederik on 05/05/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
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