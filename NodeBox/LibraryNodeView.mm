//
//  CollectionViewNodeView.mm
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "LibraryNodeView.h"
#import "NodeBoxDocument.h"

@implementation LibraryNodeView

- (void)setSelected:(BOOL)flag
{
  selected = flag;
}

- (BOOL)selected
{
  return selected;
}

- (void)drawRect:(NSRect)rect
{
    if (selected) {
        if ([[self window] isKeyWindow]) {
            [[NSColor selectedControlColor] set];
        } else {
            [[NSColor colorForControlTint:NSClearControlTint] set];
        }
        NSRectFill([self bounds]);    
    }
    [super drawRect:rect];
}

- (void)setDescription:(NSString*)description
{
    NSLog(@"setting description to %@ %@", description, myLabel);
    [myLabel setTitleWithMnemonic:description];
}

- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender
{
    NSLog(@"prepare dragging");
    return YES;
}

#pragma mark Drag and Drop

- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent
{
    return TRUE;
}

- (void)mouseDown:(NSEvent *)theEvent
{
    NSLog(@"dragging");
    NSRect r = [self bounds];
    NSImage *dragImage = [[NSImage alloc] initWithSize:NSMakeSize(r.size.width, r.size.height)];
    [dragImage lockFocus];
    [[NSColor redColor] set];
    NSRectFill(r);
    [self drawRect:[self bounds]];
    [dragImage unlockFocus];

    NSPasteboard *pboard;
    pboard = [NSPasteboard pasteboardWithName:NSDragPboard];
    [pboard declareTypes:[NSArray arrayWithObject:NodeType]  owner:self];
    [pboard setString:@"NodeString" forType:NodeType];
    
    [self dragImage:dragImage at:NSZeroPoint offset:NSZeroSize
        event:theEvent pasteboard:pboard source:self slideBack:YES];
}

@end
