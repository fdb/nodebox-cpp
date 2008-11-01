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

#import "NXDragControl.h"

@implementation NXDragCell

- (id)init {
    self = [super init];
    if (self) {
        [self setFloatValue: 0.0];
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    if ([coder allowsKeyedCoding]) {
        value = [[[coder decodeObjectForKey: @"float"] retain] floatValue];
    } else {
        value = [[[coder decodeObject] retain] floatValue];
    }
    return self;
}

- (void)encodeWithCoder:(NSCoder *)coder {
    [super encodeWithCoder:coder];
    NSNumber *number = [NSNumber numberWithFloat:[self floatValue]];
    if ([coder allowsKeyedCoding]) {
        [coder encodeObject: number forKey: @"time"];
    } else {
        [coder encodeObject: number];
    }
    [number release];
}

- (id)copyWithZone:(NSZone *)zone {
    NXDragCell *newCopy = [[NXDragCell alloc] init];
    [newCopy setFloatValue: [self floatValue]];
    return newCopy;
}

- (void)sendActionToTarget {
    if ([self target] && [self action]) {
        [(NSControl *)[self controlView] sendAction:[self action] to:[self target]];
    }
}

//// Setting and getting values ////

- (void)increaseValue:(float)delta
{
    [self setFloatValue:[self floatValue] + delta];
}

- (void)decreaseValue:(float)delta
{
    [self setFloatValue:[self floatValue] - delta];
}

- (void)setObjectValue:(NSObject *)object {
    if ([object isKindOfClass: [NSNumber class]]) {
        [self setFloatValue: [(NSNumber *)object floatValue]];
    } else {
        [NSException raise: NSInvalidArgumentException format: @"%@ Invalid object %@", NSStringFromSelector(_cmd), object];
    }
}

- (id)objectValue {
    return [[NSNumber numberWithFloat:value] autorelease];
}

- (void)setFloatValue:(float)v {
    value = v;
	[(NSControl *)[self controlView] updateCell: self];
	[self sendActionToTarget];
}

- (float)floatValue {
    return value;
}

//// Drawing ////

- (NSRect)leftButtonRect:(NSRect)cellFrame
{
    NSRect r = NSInsetRect(cellFrame, 2.0f, 2.0f);
    return NSMakeRect(r.origin.x, r.origin.y, r.size.height, r.size.height);
}

- (NSRect)rightButtonRect:(NSRect)cellFrame
{
    NSRect r = NSInsetRect(cellFrame, 1.0f, 2.0f);
    return NSMakeRect(r.size.width - r.size.height, r.origin.y, r.size.height, r.size.height);    
}

- (void)drawArrowInRect:(NSRect)r direction:(int)dir
{
    float cx = r.origin.x + r.size.width / 2;
    float cy = r.origin.y + r.size.height / 2;
    float blockSize = r.size.width / 6.0f;
    NSBezierPath *p = [NSBezierPath bezierPath];
    [p moveToPoint:NSMakePoint(cx + blockSize * -1 * dir, cy + blockSize * 2)];
    [p lineToPoint:NSMakePoint(cx + blockSize * 2 * dir, cy)];
    [p lineToPoint:NSMakePoint(cx + blockSize * -1 * dir, cy + blockSize * -2)];
    [p fill];
}

- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView {
    [[NSColor grayColor] set];
    [[NSBezierPath bezierPathWithRoundedRect:cellFrame xRadius:7.5f yRadius:7.5f] fill];

    [[NSColor darkGrayColor] set];    
    NSRect leftButtonRect = [self leftButtonRect:cellFrame];
    NSRect rightButtonRect = [self rightButtonRect:cellFrame];
    [[NSBezierPath bezierPathWithOvalInRect:leftButtonRect] fill];
    [[NSBezierPath bezierPathWithOvalInRect:rightButtonRect] fill];
    [[NSColor whiteColor] set];
    [self drawArrowInRect:leftButtonRect direction:-1];    
    [self drawArrowInRect:rightButtonRect direction:1];
    
    NSMutableParagraphStyle *style = [[NSMutableParagraphStyle alloc] init];
    [style setAlignment:NSCenterTextAlignment];
    NSDictionary *attrs = [NSDictionary dictionaryWithObjectsAndKeys:
        [NSFont fontWithName:@"LucidaGrande-Bold" size:10], NSFontAttributeName,
        [NSColor blackColor], NSForegroundColorAttributeName,
        style, NSParagraphStyleAttributeName,
        nil, nil];
        
    NSRect textRect = NSInsetRect(cellFrame, 15, 1);
    
    [[NSString stringWithFormat:@"%.1f", [self floatValue]] drawInRect:textRect withAttributes:attrs];
}

//// Tracking ////

- (BOOL)trackMouseForNumberChangeEvent:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView
{
    NSPoint startPoint = [controlView convertPoint:[theEvent locationInWindow] fromView:nil];
    float startValue = [self floatValue];
    float delta = 0.0f;

    NSEvent *currentEvent = nil;
    currentEvent = theEvent;

    do {
        NSPoint mousePoint = [controlView convertPoint: [currentEvent locationInWindow] fromView:nil];
        switch ([currentEvent type]) {
            case NSLeftMouseDown:
            case NSLeftMouseDragged:
                delta =  mousePoint.x - startPoint.x;
                [self setFloatValue:startValue + delta];
                [(NSControl *)controlView updateCell: self];
                break;
            default:
                return YES;
        }
    } while (currentEvent = [[controlView window] nextEventMatchingMask:(NSLeftMouseDraggedMask  | NSLeftMouseUpMask) untilDate:[NSDate distantFuture] inMode:NSEventTrackingRunLoopMode dequeue:YES]);
    return YES;
}

- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView untilMouseUp:(BOOL)flag {
    NSPoint pt = [controlView convertPoint:[theEvent locationInWindow] fromView:nil];

    if (NSPointInRect(pt, [self leftButtonRect:cellFrame])) {
        [self decreaseValue:1.0f];
    } else if (NSPointInRect(pt, [self rightButtonRect:cellFrame])) {
        [self increaseValue:1.0f];
    } else if ([theEvent clickCount] == 2) {
        NSTextField *field = [[NSTextField alloc] init];
        NSRect textFieldRect = NSInsetRect([self.controlView bounds], 15, 1);
        NSLog(@"tfr %f %f %f %f", textFieldRect.origin.x, textFieldRect.origin.y, textFieldRect.size.width, textFieldRect.size.height);
        [field setFrame:textFieldRect];
        [[field cell] setControlSize:NSMiniControlSize];
        [[field cell] setFont:[NSFont fontWithName:@"LucidaGrande-Bold" size:10]];
        [[field cell] setControlTint:NSGraphiteControlTint];
        [[field cell] setBackgroundStyle:NSBackgroundStyleDark];
        [[field cell] setFocusRingType: NSFocusRingTypeNone];
        [[field cell] setAlignment:NSCenterTextAlignment];
        [field setTarget:self.controlView];
        [field setAction:@selector(fieldChanged:)];
        [field setEditable:TRUE];
        [field setFloatValue:[self floatValue]];
        [field selectText:nil];
        [field setBordered:FALSE];
        [field setBackgroundColor:[NSColor grayColor]];
        NSNumberFormatter* floatFormatter = [[NSNumberFormatter alloc] init];
        [floatFormatter setFormat: @"0.0"];
        [field setFormatter:floatFormatter];
        [self.controlView addSubview:field];
        [[self.controlView window] makeFirstResponder:field];
    } else {
        NSLog(@"start the track %f %f", pt.x, pt.y);
        [self trackMouseForNumberChangeEvent:theEvent inRect:cellFrame ofView:controlView];
    }
    return YES;
}

@end


@implementation NXDragControl

+ (void)initialize {
    if (self == [NXDragControl class]) {
        [self setCellClass: [NXDragCell class]];
    }
}

+ (Class)cellClass {
    return [NXDragCell class];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

- (void)fieldChanged:(id)sender
{
    [[self cell] setFloatValue:[sender floatValue]];
    NSTextField *field = [[self subviews] objectAtIndex:0];
    [field removeFromSuperview];
}

@end
