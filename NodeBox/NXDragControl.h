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
 
#import <Cocoa/Cocoa.h>

@interface NXDragCell : NSActionCell {
    float value;
}

- (NSRect)leftButtonRect:(NSRect)cellFrame;
- (NSRect)rightButtonRect:(NSRect)cellFrame;
- (void)increaseValue:(float)delta;
- (void)decreaseValue:(float)delta;
- (void)drawArrowInRect:(NSRect)r direction:(int)dir;
@end

@interface NXDragControl : NSControl {
}

- (void)fieldChanged:(id)sender;
@end
