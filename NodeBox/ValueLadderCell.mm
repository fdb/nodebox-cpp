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

#import "ValueLadderCell.h"


@implementation ValueLadderCell

+ (BOOL)prefersTrackingUntilMouseUp
{
  //NSLog(@"prefersTrackingUntilMouseUp");
  return YES;
}

- (id)init
{
    self = [super init];
    NSLog(@"VLC init");
    return self;

}

- (id)initWithCoder:(NSCoder *)aDecoder {
  if ((self = [super initWithCoder:aDecoder])) {
   [self setContinuous:TRUE];
    NSLog(@"inti value ladder coder ");
  }
  return self;
}

- (void) drawInteriorWithFrame: (NSRect)cellFrame inView: (NSView*)controlView
{    
    NSString *floatString = [NSString stringWithFormat:@"%.3f", [self floatValue]];
    [floatString drawInRect:cellFrame withAttributes:NULL];
}


- (void)stopTracking:(NSPoint)lastPoint at:(NSPoint)stopPoint inView:(NSView *)controlView mouseIsUp:(BOOL)flag
{
    NSLog(@"stop tracking");
}

- (BOOL)continueTracking:(NSPoint)lastPoint at:(NSPoint)currentPoint inView:(NSView *)controlView
{
    NSLog(@"Continue tracking");
    return YES;
}

@end
