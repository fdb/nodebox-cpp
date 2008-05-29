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

#import "NodeLayer.h"
#import "CGColorHelper.h"

static float kNodeWidth = 80.0f;
static float kNodeHeight = 24.0f;

@implementation NodeLayer

@synthesize node;
@synthesize selected;

- (id)initWithNode:(NodeCore::Node *)anode
{
    self = [super init];
    node = anode;
    self.name = [NSString stringWithCString:node->getName().c_str()];
    self.frame = CGRectMake(node->getX(), node->getY(), kNodeWidth, kNodeHeight);
    //nodeLayer.position = CGPointMake(node->getX(), NSHeight(self.bounds) - node->getY());
    self.backgroundColor = [CGColorHelper lightGray];
    self.shadowColor = [CGColorHelper black];
    self.shadowOpacity = 0.5f;
    self.cornerRadius = 3.0f;
    self.shadowOffset = CGSizeMake(1.0f, -1.0f);
    self.shadowRadius = 2.0f;
    self.borderColor = [CGColorHelper gray];
    [self setNeedsDisplay];


    return self;



}

- (void)setSelected:(BOOL)aselected
{
    selected = aselected;
    if (selected) {
        self.borderWidth = 2.0f;
    } else {
        self.borderWidth = 0.0f;
    }
}

- (void)drawInContext:(CGContextRef)ctx
{
    NSLog(@"draw");
    CGContextSetFillColorWithColor(ctx, [CGColorHelper black]);
    CGContextSelectFont(ctx, "Lucida Grande", 13, kCGEncodingMacRoman);
    CGContextShowTextAtPoint(ctx, 10.0f, 5.0f, node->getName().c_str(), node->getName().length());
}

@end
