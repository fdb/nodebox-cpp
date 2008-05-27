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
    [myLabel setTitleWithMnemonic:description];
}

#pragma mark Drag and Drop

- (BOOL)acceptsFirstMouse:(NSEvent *)theEvent
{
    return TRUE;
}

- (BOOL)prepareForDragOperation:(id <NSDraggingInfo>)sender
{
    return YES;
}

- (void)mouseDown:(NSEvent *)theEvent
{
    NSRect r = [self bounds];
    NSImage *dragImage = [[NSImage alloc] initWithSize:NSMakeSize(r.size.width, r.size.height)];
    [dragImage lockFocus];
    [[[NSColor whiteColor] colorWithAlphaComponent:0.8] set];
    NSRectFill(r);
    [[[NSColor lightGrayColor] colorWithAlphaComponent:0.8] set];
    NSFrameRect(r);
    NSColor *c= [[NSColor darkGrayColor] colorWithAlphaComponent:0.8];
    NSDictionary *attrs = [NSDictionary dictionaryWithObject:c forKey:NSForegroundColorAttributeName];
    [[myLabel stringValue] drawAtPoint:NSMakePoint(10, 50) withAttributes:attrs];
    [dragImage unlockFocus];

    NSPasteboard *pboard;
    pboard = [NSPasteboard pasteboardWithName:NSDragPboard];
    [pboard declareTypes:[NSArray arrayWithObject:NodeType]  owner:self];
    [pboard setString:@"NodeString" forType:NodeType];
    
    [self dragImage:dragImage at:NSZeroPoint offset:NSZeroSize
        event:theEvent pasteboard:pboard source:self slideBack:YES];
}

@end
