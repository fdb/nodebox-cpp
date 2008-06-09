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
#import "NetworkLayer.h"
#import "ParameterWrapper.h"

@interface NetworkView(Private)

- (NodeLayer*) findLayerForNode: (NodeCore::Node*)node;

@end

@implementation NetworkView

- (void)awakeFromNib
{
    self.layer = [CALayer layer];
    self.layer.name = @"__top";
    self.wantsLayer = YES;
    self.layer.backgroundColor = [CGColorHelper white];
    rootNetworkLayer = [[NetworkLayer alloc] initWithNetwork:[viewController rootNetwork]];
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

#pragma mark Controller

- (NetworkViewController*)controller
{
    return viewController;
}

- (void) setController: (NetworkViewController*)controller
{
    viewController = controller;
    [self rebuildNetwork];
}

#pragma mark Mouse Events

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)mouseDown:(NSEvent *)theEvent
{
    _draggingNode = NULL;
    NSPoint eventPoint = [theEvent locationInWindow];
    NSPoint pt = [self convertPoint:eventPoint fromView:NULL];
    if (!viewController) return;
    NodeCore::Network* network = [viewController activeNetwork];
    if (!network) return;
    NodeCore::Node *node = [self findNodeAt:pt];
    if (!node) return;
    BOOL shiftKeyDown = ([[NSApp currentEvent] modifierFlags] &
        (NSShiftKeyMask | NSAlphaShiftKeyMask)) !=0; 
    _startedDragging = false;
    _draggingNode = node;
    _dragMode = shiftKeyDown ? kDragModeConnect : kDragModeNode;
    _clickPoint = NSMakePoint(node->getX() - pt.x, node->getY() - pt.y);
    _dragPoint = pt;
    // TODO: When making a connection, show the connection line
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    if (_draggingNode == NULL) return;
    if (!viewController) return;
    NodeCore::Network* network = [viewController activeNetwork];
    if (!network) return;
    NSPoint eventPoint = [theEvent locationInWindow];
    NSPoint pt = [self convertPoint:eventPoint fromView:NULL];
    if (!_startedDragging &&
        abs(pt.x + _clickPoint.x - _draggingNode->getX()) > kDragStart ||
        abs(pt.y + _clickPoint.y - _draggingNode->getY()) > kDragStart) {
        _startedDragging = true;
    }
    if (_startedDragging) {
        _dragPoint = pt;
        if (_dragMode == kDragModeNode) {
            NSPoint newPos = NSMakePoint(pt.x + _clickPoint.x, pt.y + _clickPoint.y);
            [viewController.windowController moveNode:_draggingNode to:newPos];
        } else if (_dragMode == kDragModeConnect) {
            NodeCore::Node *newDragOverNode = [self findNodeAt:pt];
            if (_dragOverNode == newDragOverNode) return;
            [self dehighlightNode:_dragOverNode];
            _dragOverNode = newDragOverNode;
            [self highlightNode:_dragOverNode];
        }
    }
}

- (void)mouseUp:(NSEvent *)theEvent
{
    // If I was dragging, should not select.
    NSPoint eventPoint = [theEvent locationInWindow];
    NSPoint pt = [self convertPoint:eventPoint fromView:NULL];
    if (!viewController) return;
    if (_startedDragging && _dragMode == kDragModeConnect && _dragOverNode != NULL) {
        [self dehighlightNode:_dragOverNode];
        if (_dragOverNode != _draggingNode) {
            _deferredDraggingNode = _draggingNode;
            NSMenu *parameterMenu = [[NSMenu alloc] init];
            SEL connectSelector = @selector(connectNodeToParameter:);
            NodeCore::ParameterList parameters = _dragOverNode->getParameters();
            for (NodeCore::ParameterIterator parameterIter = parameters.begin(); parameterIter != parameters.end(); ++parameterIter) {
                NodeCore::Parameter *parameter = *parameterIter;
                NSMenuItem *item = [parameterMenu addItemWithTitle:[NSString stringWithCString:parameter->getName().c_str()] action:connectSelector keyEquivalent:@""];
                ParameterWrapper *parameterWrapper = [[ParameterWrapper alloc] initWithParameter:parameter];
                [item setRepresentedObject:parameterWrapper];
            }
            [NSMenu popUpContextMenu:parameterMenu withEvent:theEvent forView:self];
            _draggingNode = NULL;
            _startedDragging = false;
            _dragMode = kDragModeNotDragging;
            _dragOverNode = NULL;
        }
    }
    if ([theEvent clickCount] == 1) {
        // Select a node
        [viewController.windowController setActiveNode:[self findNodeAt:pt]];
    } else if ([theEvent clickCount] == 2) {
        [viewController.windowController setRenderedNode:[self findNodeAt:pt]];
    }
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
    if (!viewController) return;
    NodeCore::Network* network = [viewController activeNetwork];
    if (!network) return;
    NSPoint eventPoint = [theEvent locationInWindow];
    NSPoint pt = [self convertPoint:eventPoint fromView:NULL];
    NodeCore::Node *node = [self findNodeAt:pt];
    if (!node) return;
    [(NetworkViewController *)viewController contextMenuForNode:node event:theEvent];
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

#pragma mark View queries

- (NodeCore::Node*) findNodeAt: (NSPoint)point
{
    CALayer *hit = [rootNetworkLayer hitTest:CGPointMake(point.x, point.y)];
    if (!hit) return NULL;
    NodeCore::Node *node = [viewController rootNetwork]->getNode([[hit name] UTF8String]);
    return node;
}

#pragma mark View operations

- (void) clearLayers;
{
    while (rootNetworkLayer.sublayers > 0) {
        CALayer *sublayer = (CALayer *)[rootNetworkLayer.sublayers objectAtIndex:0];
        [sublayer removeFromSuperlayer];
    }
}

- (void) rebuildNetwork;
{
    [self clearLayers];
    NodeCore::Network* network = [viewController rootNetwork];
    if (!network) return;
    NodeCore::NodeList nodes = network->getNodes();
    for (NodeCore::NodeIterator nodeIter = nodes.begin(); nodeIter != nodes.end(); ++nodeIter) {
        NodeCore::Node* node = (*nodeIter);
        [self addLayerForNode:node];
    }
    [self select:[viewController activeNode]];
}

- (void) moveNode: (NodeCore::Node*)node to: (NSPoint)pt;
{
    NodeLayer *nodeLayer = [self findLayerForNode:node];
    if (!nodeLayer) return;
    nodeLayer.position = CGPointMake(pt.x, pt.y);
}

- (void) deselect;
{
    NSArray *sublayers = [rootNetworkLayer sublayers];
    for (int i=0; i < [sublayers count]; i++) {
        NodeLayer *sublayer = (NodeLayer *)[sublayers objectAtIndex:i];
        sublayer.selected = FALSE;
    }
}

- (void) select: (NodeCore::Node*)node;
{
    NodeLayer *layer = (NodeLayer *)[self findLayerForNode:node];
    layer.selected = TRUE;
}

- (void) setRenderedNode: (NodeCore::Node*)node
{
    NSArray *sublayers = [rootNetworkLayer sublayers];
    for (int i=0; i < [sublayers count]; i++) {
        NodeLayer *sublayer = (NodeLayer *)[sublayers objectAtIndex:i];
        if (sublayer.node == node) {
            sublayer.rendered = TRUE;
        } else {
            sublayer.rendered = FALSE;
        }
    }
}

- (void) addLayerForNode: (NodeCore::Node*)node
{
    NodeLayer *nodeLayer  = [[NodeLayer alloc] initWithNode:node];
    [rootNetworkLayer addSublayer:nodeLayer];    
}

- (void) removeLayerForNode: (NodeCore::Node*)node
{
    NodeLayer *nodeLayer = [self findLayerForNode:node];
    if (!nodeLayer) return;
    [nodeLayer removeFromSuperlayer];
}

- (void) highlightNode: (NodeCore::Node*)node
{
    if (!node) return;
    NodeLayer *layer = [self findLayerForNode:node];
    if (!layer) return;
    layer.shadowColor = [CGColorHelper dragHighlightColor];
    layer.shadowOpacity = 1.0f;
    layer.shadowRadius = 5.0f;
}

- (void) dehighlightNode: (NodeCore::Node*)node
{
    if (!node) return;
    NodeLayer *layer = [self findLayerForNode:node];
    if (!layer) return;
    layer.shadowColor = [CGColorHelper black];
    layer.shadowOpacity = 0.5f;
    layer.shadowRadius = 2.0f;
}

- (void) redrawConnections
{
    [rootNetworkLayer setNeedsDisplay];
}

#pragma mark Event callbacks

- (void) connectNodeToParameter: (NSMenuItem*)menuItem
{
    if (!_deferredDraggingNode) return;
    NodeCore::Parameter *parameter = [(ParameterWrapper *)[menuItem representedObject] parameter];
    if (!parameter) return;
    [viewController.windowController connectFrom:parameter to:_deferredDraggingNode];
    _deferredDraggingNode = NULL;
}

@end

@implementation NetworkView(Private)

- (NodeLayer*) findLayerForNode: (NodeCore::Node*)node
{
    if (!node) return NULL;
    NSString *nodeName = [NSString stringWithCString:node->getName().c_str()];
    NSArray *sublayers = [rootNetworkLayer sublayers];
    for (int i=0; i < [sublayers count]; i++) {
        CALayer *sublayer = (CALayer *)[sublayers objectAtIndex:i];
        if ([sublayer.name isEqualToString:nodeName]) {
            return (NodeLayer*) sublayer;
        }
    }
    return NULL;
}

@end
