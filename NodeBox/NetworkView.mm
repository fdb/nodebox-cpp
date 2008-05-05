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

@implementation NetworkView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        visualiser = new NetworkVisualiser();
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
        visualiser->set("network", (void*)network);
        visualiser->update();
        NodeCore::Canvas canvas = visualiser->outputAsCanvas();
        CGContextRef ctx = (CGContextRef) [[NSGraphicsContext currentContext] graphicsPort];
        canvas._draw(ctx);
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

@end
