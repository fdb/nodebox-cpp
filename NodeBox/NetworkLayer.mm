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

#import "NetworkLayer.h"
#import "CGColorHelper.h"

@interface NetworkLayer(Private)

    - (void)drawConnectionFrom:(NodeCore::Parameter *)output to:(NodeCore::Parameter *)input context:(CGContextRef)ctx;
    - (void)drawConnectionLineFrom:(NSPoint)p1 to:(NSPoint)p2 context:(CGContextRef)ctx;

@end

@implementation NetworkLayer

- (id)initWithNetwork:(NodeCore::Network *)network
{
    self = [super initWithNode:network];
    self.needsDisplayOnBoundsChange = TRUE;
    return self;
}

- (NodeCore::Network *)network
{
    return (NodeCore::Network *)self.node;
}

- (void)drawInContext:(CGContextRef)ctx
{
    NodeCore::NodeList nodes = self.network->getNodes();
    for (NodeCore::NodeIterator nodeIter = nodes.begin(); nodeIter != nodes.end(); ++nodeIter) {
        NodeCore::Node* theNode = (*nodeIter);
        NodeCore::ConnectionList downstreams = theNode->getOutputConnections();
        for (NodeCore::ConnectionIterator connIter = downstreams.begin(); connIter != downstreams.end(); ++connIter) {
            NodeCore::Connection *conn = (*connIter);
            [self drawConnectionFrom:conn->getInputParameter() to:conn->getOutputParameter() context:ctx];
        }        
    }
}

- (void)drawConnectionFrom:(NodeCore::Parameter *)output to:(NodeCore::Parameter *)input context:(CGContextRef)ctx
{
    NodeCore::Node *inputNode = input->getNode();
    NodeCore::Node *outputNode = output->getNode();
    NSPoint p1 = NSMakePoint(outputNode->getX(), outputNode->getY() + kNodeHeight/2);
    NSPoint p2 = NSMakePoint(inputNode->getX(), inputNode->getY() - kNodeHeight/2);
    [self drawConnectionLineFrom:p1 to:p2 context:ctx];
}

- (void)drawConnectionLineFrom:(NSPoint)p1 to:(NSPoint)p2 context:(CGContextRef)ctx
{
    float dx = abs(p2.x - p1.x) / 2;
    CGContextMoveToPoint(ctx, p1.x, p1.y);
    CGContextAddCurveToPoint(ctx, p1.x, p1.y + dx, p2.x, p2.y - dx, p2.x, p2.y);
    CGContextSetLineWidth(ctx, 2.0);
    CGContextSetStrokeColorWithColor(ctx, [CGColorHelper connectionLineColor]);
    CGContextStrokePath(ctx);
}

@end
