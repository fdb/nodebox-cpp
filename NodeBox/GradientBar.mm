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
 
#import "GradientBar.h"


@implementation GradientBar

- (id)initWithFrame:(NSRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        NSColor *topBottomColor = [NSColor colorWithDeviceRed:0.96 green:0.96 blue:0.96 alpha:1.0];
        NSColor *bottomTopColor = [NSColor colorWithDeviceRed:0.9 green:0.9 blue:0.9 alpha:1.0];
        NSColor *bottomBottomColor = [NSColor colorWithDeviceRed:0.85 green:0.85 blue:0.85 alpha:1.0];
        topGradient = [[NSGradient alloc] initWithStartingColor:[NSColor whiteColor] endingColor:topBottomColor];
        bottomGradient = [[NSGradient alloc] initWithStartingColor:bottomTopColor endingColor:bottomBottomColor];
    }
    return self;
}

- (void)drawRect:(NSRect)rect {
    [topGradient drawInRect:NSMakeRect(rect.origin.x, rect.origin.y+rect.size.height/2, rect.size.width, rect.size.height/2) angle:-90];
    [bottomGradient drawInRect:NSMakeRect(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height/2) angle:-90];
    [[NSColor colorWithDeviceWhite:0.79 alpha:1.0] set];
    NSRectFill(NSMakeRect(rect.origin.x, rect.origin.y + rect.size.height - 1, rect.size.width, 1));
}

@end
