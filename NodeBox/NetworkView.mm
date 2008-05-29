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

static float kNodeWidth = 80.0f;
static float kNodeHeight = 24.0f;

@interface NetworkView(Private)

    - (void)addLayerForNode:(NodeCore::Node *)node;
    - (CGImageRef)imageForNode:(NodeCore::Node *)node;
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
    rootNetworkLayer.backgroundColor = [CGColorHelper halfRed];
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
    NSLog(@"Canvas view mouse down");
}

- (void)mouseUp:(NSEvent *)theEvent
{
    NSLog(@"mouseup");
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
    NSLog(@"hit %@", hit.name);
    if (!hit) return NULL;
    NodeCore::Node *node = [viewController rootNetwork]->getNode([[hit name] UTF8String]);
    if (node) {
        NSLog(@"found %s", node->getName().c_str());
    } else {
        NSLog(@"didnt find");
    }
    return node;
}

- (void)activeNodeChanged:(NodeCore::Node *)activeNode
{
    NSLog(@"active changed");
    [self deselect];
    [self select:activeNode];
}

+ (NSDictionary *)deselectedStyle
{
    return [NSDictionary dictionaryWithObjectsAndKeys: (id)[CGColorHelper black], @"borderColor",
                                                0.0f, @"borderWidth",
                                                0.2f, @"shadowOpacity",
                                                nil, nil];
}

+ (NSDictionary *)selectedStyle
{
    return [NSDictionary dictionaryWithObjectsAndKeys: (id)[CGColorHelper blue], @"borderColor",
                                                2.0f, @"borderWidth",
                                                1.0f, @"shadowOpacity",
                                                nil, nil];
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
        NSLog(@"Adding node %s", node->getName().c_str());
        [self addLayerForNode:node];
    }
}

@end

@implementation NetworkView(Private)

- (void)addLayerForNode:(NodeCore::Node *)node
{
    NSLog(@"Adding layer %s", node->getName().c_str());
    CALayer *nodeLayer = [CALayer layer];
    nodeLayer.name = [NSString stringWithCString:node->getName().c_str()];
    nodeLayer.frame = CGRectMake(node->getX(), node->getY(), kNodeWidth, kNodeHeight);
    //nodeLayer.position = CGPointMake(node->getX(), NSHeight(self.bounds) - node->getY());
    nodeLayer.backgroundColor = [CGColorHelper halfBlue];
    nodeLayer.shadowColor = [CGColorHelper black];
    nodeLayer.shadowOpacity = 0.5f;
    nodeLayer.cornerRadius = 3.0f;
    nodeLayer.shadowOffset = CGSizeMake(1.0f, -1.0f);
    nodeLayer.shadowRadius = 2.0f;
    nodeLayer.contents = (id)[self imageForNode:node];
    [rootNetworkLayer addSublayer:nodeLayer];    
}

- (CGImageRef)imageForNode:(NodeCore::Node *)node
{
    CGColorSpaceRef colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
    CGContextRef context = CGBitmapContextCreate(NULL, kNodeWidth, 
                                                 kNodeHeight, 8, 0, 
                                                 colorSpace, 
                                                 kCGImageAlphaPremultipliedFirst);
    CGContextSetInterpolationQuality(context, kCGInterpolationHigh);
    CGContextSetFillColorWithColor(context, [CGColorHelper black]);
    CGContextSelectFont(context, "Lucida Grande", 13, kCGEncodingMacRoman);
    CGContextShowTextAtPoint(context, 10.0f, 5.0f, node->getName().c_str(), node->getName().length());
    CGContextFlush(context);
    CGImageRef image = CGBitmapContextCreateImage(context);
	CGContextRelease (context);    
    return image;
}

- (void)deselect
{
    NSArray *sublayers = [rootNetworkLayer sublayers];
    for (int i=0; i < [sublayers count]; i++) {
        CALayer *sublayer = (CALayer *)[sublayers objectAtIndex:i];
        sublayer.style = [NetworkView deselectedStyle];
        sublayer.borderWidth = 0.0f;
        sublayer.borderColor = [CGColorHelper black];
    }
    
}

- (void)select:(NodeCore::Node *)node
{
    CALayer *layer = [self findLayerForNode:node];
    layer.style = [NetworkView selectedStyle];
    layer.borderWidth = 2.0f;
    layer.borderColor = [CGColorHelper black];
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
