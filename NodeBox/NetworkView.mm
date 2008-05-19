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

float NODE_WIDTH = 100;
float NODE_HEIGHT = 25;

@implementation NetworkView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
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
}

- (void)_drawNode:(NodeCore::Node *)node
{
    NSRect r = NSMakeRect(node->getX(), node->getY(), NODE_WIDTH, NODE_HEIGHT);
    NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect:r xRadius:2 yRadius:2];
    [[NSColor lightGrayColor] set];
    [path fill];
    NSString *s = [NSString stringWithCString:node->getName().c_str()];
    [[NSColor blackColor] set];
    [s drawAtPoint:NSMakePoint(node->getX()+5, node->getY()+5) withAttributes:NULL];
}

- (void)_drawConnectionWithInputField:(NodeCore::Field *)input outputField:(NodeCore::Field *)output
{
    NodeCore::Node *inputNode = input->getNode();
    NodeCore::Node *outputNode = output->getNode();
    NSPoint p1 = NSMakePoint(outputNode->getX() + NODE_WIDTH / 2, outputNode->getY() + NODE_HEIGHT);
    NSPoint p2 = NSMakePoint(inputNode->getX() + NODE_WIDTH / 2, inputNode->getY());
    NSLog(@"p1: %.2f,%.2f p2: %.2f,%.2f", p1.x, p1.y, p2.x, p2.y);
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

@end
