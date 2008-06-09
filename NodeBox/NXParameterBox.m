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

#import "NXParameterBox.h"

@implementation NXParameterBox

- (void)drawRect:(NSRect)rect
{
    [[NSColor colorWithDeviceWhite:0.8f alpha:1.0f] set];
    NSRectFill(rect);
    [[NSColor colorWithDeviceWhite:0.75f alpha:1.0f] set];
    NSRectFill(NSMakeRect(rect.origin.x, rect.origin.y, rect.size.width, 1));
    NSRectFill(NSMakeRect(rect.origin.x+100, rect.origin.y, 1, rect.size.height));
}

@end
