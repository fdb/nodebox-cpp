//
//  NetworkView.m
//  NodeBox
//
//  Created by Frederik on 05/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "NetworkView.h"
#import "NetworkViewController.h"
#import "NetworkVisualiser.h"
#import "NodeBoxDocument.h"
#import "NodeBoxWindowController.h"

float NODE_WIDTH = 121;
float NODE_HEIGHT = 30;
float CONNECTOR_RADIUS = 5;
float DRAG_START = 5;

@implementation NetworkView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        _dragMode = kDragModeNotDragging;
        _draggingNode = NULL;
        _dragOverNode = NULL;
        _dragPoint = NSMakePoint(0, 0);
        _startedDragging = false;
        _deferredDraggingNode = NULL;
        _clickPoint = NSMakePoint(0, 0);
        visualiser = new NetworkVisualiser();
        [self registerForDraggedTypes:[NSArray arrayWithObjects:NodeType, nil]];
    }
    return self;
}

-(void)dealloc
{
    delete visualiser;
    [super dealloc];
}

-(BOOL)isFlipped
{
    return TRUE;
}

-(BOOL)canBecomeKeyView
{
    return TRUE;
}

-(BOOL)acceptsFirstResponder
{
    return TRUE;
}

- (void)awakeFromNib
{
    NSLog(@"NetworkView awakened contr %@", viewController);
}

- (NetworkViewController*)controller
{
    return viewController;
}

- (void)setController:(NetworkViewController *)controller
{
    viewController = controller;
    [self setNeedsDisplay:TRUE];
}

#pragma mark Drawing

- (void)drawRect:(NSRect)rect
{
    [[NSColor redColor] set];
    NSRectFill(rect);
    if (!viewController) return;
    NodeCore::Network* network = [viewController activeNetwork];
    if (!network) return;
    [[NSColor whiteColor] set];
    NSRectFill(rect);
    NodeCore::NodeList nodes = network->getNodes();
    for (NodeCore::NodeIterator nodeIter = nodes.begin(); nodeIter != nodes.end(); ++nodeIter) {
        NodeCore::Node* node = (*nodeIter);
        NodeCore::ConnectionList downstreams = node->getOutputConnections();
        for (NodeCore::ConnectionIterator connIter = downstreams.begin(); connIter != downstreams.end(); ++connIter) {
            NodeCore::Connection *conn = (*connIter);
            [self _drawConnectionWithInputField:conn->getInputField() outputField:conn->getOutputField()];
        }        
    }
    for (NodeCore::NodeIterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
        NodeCore::Node* node = (*iter);
        [self _drawNode:node];
    }
    if (_startedDragging && _dragMode == kDragModeConnect) {
        NSPoint p1 = NSMakePoint(_draggingNode->getX() + NODE_WIDTH / 2, _draggingNode->getY() + NODE_HEIGHT);
        [self _drawConnectionLineFrom:p1 to:_dragPoint];
    }
}

- (void)_drawNode:(NodeCore::Node *)node
{
    NSColor *nodeColor;
    if (node == _dragOverNode) {
        nodeColor = [NSColor blueColor];
    //} else if (node->hasError) {
    //    [[NSColor redColor] set];
    } else {
        nodeColor = [NSColor blackColor];
    }
    [nodeColor set];
    NSRect r = NSMakeRect(node->getX(), node->getY(), NODE_WIDTH, NODE_HEIGHT);
    NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect:r xRadius:2 yRadius:2];
    [path fill];
    if (node == [viewController activeNode]) {
        [path setLineWidth:3.0];
        [[NSColor colorWithDeviceWhite:0.8 alpha:1.0] set];
    } else {
        [path setLineWidth:1.0];
        [[NSColor colorWithDeviceWhite:0.3 alpha:1.0] set];
    }
    [path stroke];
    NSRect connectorRect = NSMakeRect(node->getX() + NODE_WIDTH / 2 - CONNECTOR_RADIUS, node->getY() + NODE_HEIGHT - CONNECTOR_RADIUS - 1,
               CONNECTOR_RADIUS * 2, CONNECTOR_RADIUS * 2);
    NSBezierPath *connectorPath = [NSBezierPath bezierPathWithOvalInRect:connectorRect];
    [nodeColor set];
    [connectorPath fill];
    NSString *s = [NSString stringWithCString:node->getName().c_str()];
    NSColor *c= [NSColor colorWithDeviceWhite:0.9 alpha:1.0];
    NSDictionary *attrs = [NSDictionary dictionaryWithObject:c forKey:NSForegroundColorAttributeName];
    [s drawAtPoint:NSMakePoint(node->getX()+5, node->getY()+5) withAttributes:attrs];
}

- (void)_drawConnectionWithInputField:(NodeCore::Field *)input outputField:(NodeCore::Field *)output
{
    NodeCore::Node *inputNode = input->getNode();
    NodeCore::Node *outputNode = output->getNode();
    NSPoint p1 = NSMakePoint(outputNode->getX() + NODE_WIDTH / 2, outputNode->getY() + NODE_HEIGHT);
    NSPoint p2 = NSMakePoint(inputNode->getX() + NODE_WIDTH / 2, inputNode->getY());
    [self _drawConnectionLineFrom:p1 to:p2];
}

- (void)_drawConnectionLineFrom:(NSPoint)p1 to:(NSPoint)p2
{
    float dx = abs(p2.x - p1.x) / 2;
    NSBezierPath *path = [NSBezierPath bezierPath];
    [path moveToPoint:p1];
    [path curveToPoint:p2 
         controlPoint1:NSMakePoint(p1.x, p1.y + dx) 
         controlPoint2:NSMakePoint(p2.x, p2.y - dx)];
    [path setLineWidth:2.0];
    [[NSColor colorWithDeviceWhite:0.3 alpha:1.0] set];
    [path stroke];
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
        NSPoint dragPoint = [sender draggingLocation];
        dragPoint = [self convertPointFromBase:dragPoint];
        [[viewController windowController] createNodeAt:dragPoint];
        [self setNeedsDisplay:TRUE];
        // Only a copy operation allowed so just copy the data
        return YES;
    } else {
        return NO;
    }
}

#pragma mark Dragging

- (void)mouseDown:(NSEvent *)theEvent
{
    _draggingNode = NULL;
    NSPoint eventPoint = [theEvent locationInWindow];
    NSPoint pt = [self convertPoint:eventPoint fromView:NULL];
    if (!viewController) return;
    NodeCore::Network* network = [viewController activeNetwork];
    if (!network) return;
    NodeCore::NodeList nodes = network->getNodes();
    for (NodeCore::NodeIterator nodeIter = nodes.begin(); nodeIter != nodes.end(); ++nodeIter) {
        NodeCore::Node* node = (*nodeIter);
        if (pt.x >= node->getX() && pt.y >= node->getY() 
            && pt.x <= node->getX() + NODE_WIDTH && pt.y <= node->getY() + NODE_HEIGHT) {
            _startedDragging = false;
            _draggingNode = node;
            _dragMode = kDragModeNode;
            _clickPoint = NSMakePoint(node->getX() - pt.x, node->getY() - pt.y);
            _dragPoint = pt;
            NSLog(@"Down on node %s", node->getName().c_str());
        } else if (pt.x >= node->getX() && pt.y >= node->getY() 
            && pt.x <= node->getX() + NODE_WIDTH && pt.y <= node->getY() + NODE_HEIGHT + CONNECTOR_RADIUS) {
            _startedDragging = false;
            _draggingNode = node;
            _dragMode = kDragModeConnect;
            _clickPoint = NSMakePoint(node->getX() - pt.x, node->getY() - pt.y);
            _dragPoint = pt;            
        }
    }
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
        abs(pt.x + _clickPoint.x - _draggingNode->getX()) > DRAG_START ||
        abs(pt.y + _clickPoint.y - _draggingNode->getY()) > DRAG_START) {
        _startedDragging = true;
    }
    if (_startedDragging) {
        _dragPoint = pt;
        if (_dragMode == kDragModeNode) {
            NSLog(@"Dragging node %s", _draggingNode->getName().c_str());
            _draggingNode->setX(pt.x + _clickPoint.x);
            _draggingNode->setY(pt.y + _clickPoint.y);
        } else if (_dragMode == kDragModeConnect) {
            _dragOverNode = [self findNodeAt:pt];
            if (_dragOverNode) { 
                NSLog(@"Drag over connection %s", _dragOverNode->getName().c_str());
            }
        }
    }
    [self setNeedsDisplay:TRUE];    
}

- (void)mouseUp:(NSEvent *)theEvent
{
}

- (NodeCore::Node *)findNodeAt:(NSPoint) point
{
    if (!viewController) return NULL;
    NodeCore::Network* network = [viewController activeNetwork];
    if (!network) return NULL;
    NodeCore::NodeList nodes = network->getNodes();
    for (NodeCore::NodeIterator nodeIter = nodes.begin(); nodeIter != nodes.end(); ++nodeIter) {
        NodeCore::Node* node = (*nodeIter);
        if (point.x >= node->getX() && point.y >= node->getY() 
            && point.x <= node->getX() + NODE_WIDTH && point.y <= node->getY() + NODE_HEIGHT) {
            return node;
        }
    }
    return NULL;
}

@end
