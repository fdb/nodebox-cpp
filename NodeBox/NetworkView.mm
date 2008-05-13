//
//  NetworkView.m
//  NodeBox
//
//  Created by Frederik on 05/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "NetworkView.h"
#import "NodeBoxDocument.h"
#import "NetworkVisualiser.h"

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

- (void)drawRect:(NSRect)rect
{
    [[NSColor redColor] set];
    NSRectFill(rect);
    if (document) {
        [[NSColor whiteColor] set];
        NSRectFill(rect);
        NodeCore::Network* network = [document network];
        NodeCore::NodeList nodes = network->getNodes();
        for (NodeCore::NodeIterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
            NodeCore::Node* node = (*iter);
            NSRect r = NSMakeRect(node->getX(), node->getY(), NODE_WIDTH, NODE_HEIGHT);
            NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect:r xRadius:2 yRadius:2];
            [[NSColor lightGrayColor] set];
            [path fill];
            NSString *s = [NSString stringWithCString:node->getName().c_str()];
            [[NSColor blackColor] set];
            [s drawAtPoint:NSMakePoint(node->getX()+5, node->getY()+5) withAttributes:NULL];
        }
    }
}

- (NodeBoxDocument*)document
{
    return document;
}

- (void)setDocument:(NodeBoxDocument*)doc
{
    NSLog(@"set document");
    if (document == doc) return;
    document = doc;
    [self setNeedsDisplay:true];
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
        [[self document] createNodeAt:dragPoint];
        [self setNeedsDisplay:TRUE];
        // Only a copy operation allowed so just copy the data
        return YES;
    } else {
        return NO;
    }
}

@end
