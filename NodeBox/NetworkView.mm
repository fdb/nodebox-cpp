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

#import "NetworkView.h"
#import <QuartzCore/QuartzCore.h>
#import "CGColorHelper.h"
#import "NetworkViewController.h"
#import "NodeInfoWrapper.h"
#import "NodeBoxWindowController.h"
#import "NodeBoxDocument.h"
#import "NodeLayer.h"

@interface NetworkView(Private)

    - (void)addLayerForNode:(NodeCore::Node *)node;
    - (void)deselect;
    - (void)select:(NodeCore::Node *)node;
    - (CALayer *)findLayerForNode:(NodeCore::Node *)node;

@end

@implementation NetworkView

- (void)awakeFromNib
{
    self.layer = [CALayer layer];
    self.layer.name = @"__top";
    self.wantsLayer = YES;
    self.layer.backgroundColor = [CGColorHelper white];
    rootNetworkLayer = [CALayer layer];
    rootNetworkLayer.frame = self.layer.frame;
    rootNetworkLayer.autoresizingMask = kCALayerWidthSizable | kCALayerHeightSizable;
    //rootNetworkLayer.bounds = CGRectMake(0.0f, 0.0f, NSWidth(self.bounds), NSHeight(self.bounds));
    //rootNetworkLayer.position = CGPointMake(0.0f, 0.0f);
    //rootNetworkLayer.anchorPoint = CGPointMake(0.0f, 0.0f);
    rootNetworkLayer.name = @"__root";
    rootNetworkLayer.backgroundColor = [CGColorHelper veryLightGray];
    [self.layer addSublayer:rootNetworkLayer];
    [self rebuildNetwork];
    [self registerForDraggedTypes:[NSArray arrayWithObjects:NodeType, nil]];
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}


- (void)mouseDown:(NSEvent *)theEvent
{
}

- (void)mouseUp:(NSEvent *)theEvent
{
    NSPoint eventPoint = [theEvent locationInWindow];
    NSPoint pt = [self convertPoint:eventPoint fromView:NULL];
    if (!viewController) return;
    //if ([theEvent clickCount] == 1) {
        // Select a node
        [viewController setActiveNode:[self findNodeAt:pt]];
        [viewController setRenderedNode:[self findNodeAt:pt]];
    //}
}

- (NetworkViewController*)controller
{
    return viewController;
}

- (void)setController:(NetworkViewController *)controller
{
    viewController = controller;
    [self rebuildNetwork];
}

#pragma mark Drag And Drop

- (NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender
{
    NSPasteboard *pboard;
    NSDragOperation sourceDragMask;
 
    sourceDragMask = [sender draggingSourceOperationMask];
    pboard = [sender draggingPasteboard];
 
    if ( [[pboard types] containsObject:NodeType] ) {
        return NSDragOperationCopy;
    }
    return NSDragOperationNone;
}

- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender
{
    NSPasteboard *pboard;
    NSDragOperation sourceDragMask;
 
    sourceDragMask = [sender draggingSourceOperationMask];
    pboard = [sender draggingPasteboard];
 
    if ( [[pboard types] containsObject:NodeType] ) {
    
        NSString *identifier = [pboard stringForType:NodeType];
        NodeInfoWrapper *wrapper = [NodeInfoWrapper wrapperWithIdentifier:identifier];
        if (!wrapper) return NO;
        NSPoint dragPoint = [sender draggingLocation];
        dragPoint = [self convertPoint:dragPoint fromView:NULL];
        [[viewController windowController] createNode:[wrapper nodeInfo] at:dragPoint];
        [self setNeedsDisplay:TRUE];
        [wrapper dealloc];
        return YES;
    } else {
        return NO;
    }
}

- (NodeCore::Node *)findNodeAt:(NSPoint) point
{
    CALayer *hit = [rootNetworkLayer hitTest:CGPointMake(point.x, point.y)];
    if (!hit) return NULL;
    NodeCore::Node *node = [viewController rootNetwork]->getNode([[hit name] UTF8String]);
    return node;
}

- (void)activeNodeChanged:(NodeCore::Node *)activeNode
{
    [self deselect];
    [self select:activeNode];
}

- (void)clearLayers
{
    while (rootNetworkLayer.sublayers > 0) {
        CALayer *sublayer = (CALayer *)[rootNetworkLayer.sublayers objectAtIndex:0];
        [sublayer removeFromSuperlayer];
    }
}

- (void)rebuildNetwork
{
    [self clearLayers];
    NodeCore::Network* network = [viewController rootNetwork];
    if (!network) return;
    NodeCore::NodeList nodes = network->getNodes();
    for (NodeCore::NodeIterator nodeIter = nodes.begin(); nodeIter != nodes.end(); ++nodeIter) {
        NodeCore::Node* node = (*nodeIter);
        [self addLayerForNode:node];
    }
}

@end

@implementation NetworkView(Private)

- (void)addLayerForNode:(NodeCore::Node *)node
{
    NodeLayer *nodeLayer  = [[NodeLayer alloc] initWithNode:node];
    [rootNetworkLayer addSublayer:nodeLayer];    
}

- (void)deselect
{
    NSArray *sublayers = [rootNetworkLayer sublayers];
    for (int i=0; i < [sublayers count]; i++) {
        NodeLayer *sublayer = (NodeLayer *)[sublayers objectAtIndex:i];
        sublayer.selected = FALSE;
    }
    
}

- (void)select:(NodeCore::Node *)node
{
    NodeLayer *layer = (NodeLayer *)[self findLayerForNode:node];
    layer.selected = TRUE;
}

- (CALayer *)findLayerForNode:(NodeCore::Node *)node
{
    if (!node) return NULL;
    NSString *nodeName = [NSString stringWithCString:node->getName().c_str()];
    NSArray *sublayers = [rootNetworkLayer sublayers];
    for (int i=0; i < [sublayers count]; i++) {
        CALayer *sublayer = (CALayer *)[sublayers objectAtIndex:i];
        if ([sublayer.name isEqualToString:nodeName]) {
            return sublayer;
        }
    }
    return NULL;
}

@end
