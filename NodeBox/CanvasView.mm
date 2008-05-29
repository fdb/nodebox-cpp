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

#import "CanvasView.h"
#import <NodeCore/NodeCore.h>

@implementation CanvasView

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
    }
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}


- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)mouseUp:(NSEvent *)theEvent
{
    NSLog(@"Canvas view mouse up");
}

- (void)mouseDown:(NSEvent *)theEvent
{
    NSLog(@"Canvas view mouse down");
}

- (void)drawRect:(NSRect)rect {
    [[NSColor redColor] set];
    NSRectFill(rect);
    NodeCore::Node *renderedNode = [viewController renderedNode];
    if (!renderedNode) return;
    renderedNode->update();
    if (renderedNode->getOutputType() == NodeCore::kCanvas) {
        CGContextRef ctx = (CGContext *) [[NSGraphicsContext currentContext] graphicsPort];
        [[NSColor grayColor] set];
        NSRectFill(rect);
        NodeCore::Canvas *canvas = (NodeCore::Canvas *) renderedNode->outputAsData();
        canvas->_draw(ctx);
    }
}

@end
