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


@implementation NodeLayer

@synthesize node;
@synthesize selected;

- (id)initWithNode:(NodeCore::Node *)anode
{
    self = [super init];
    node = anode;
    self.name = [NSString stringWithCString:node->getName().c_str()];
    self.bounds = CGRectMake(0, 0, kNodeWidth, kNodeHeight);
    self.position = CGPointMake(node->getX(), node->getY());
    self.backgroundColor = [CGColorHelper lightGray];
    self.shadowColor = [CGColorHelper black];
    self.shadowOpacity = 0.5f;
    self.shadowOffset = CGSizeMake(1.0f, -1.0f);
    self.shadowRadius = 2.0f;
    self.cornerRadius = 3.0f;
    self.borderColor = [CGColorHelper gray];
    [self setNeedsDisplay];

    return self;
}

- (void)setSelected:(BOOL)aselected
{
    selected = aselected;
    if (selected) {
        self.borderWidth = 2.0f;
        self.shadowOpacity = 0.8f;
        //self.transform = CATransform3DMakeScale(1.05f, 1.05f, 1.0f);
    } else {
        self.borderWidth = 0.0f;
        self.shadowOpacity = 0.5f;
        //self.transform = CATransform3DIdentity;
    }
}

- (void)drawInContext:(CGContextRef)ctx
{
    NSLog(@"draw");
    CGContextSetFillColorWithColor(ctx, [CGColorHelper black]);
    CGContextSelectFont(ctx, "Lucida Grande", 13, kCGEncodingMacRoman);
    CGContextShowTextAtPoint(ctx, 10.0f, 5.0f, node->getName().c_str(), node->getName().length());
}

+ (id<CAAction>)defaultActionForKey:(NSString *)aKey
{
    // TODO: Can't use a static obj for some reason. 
    // on initialization, the object is suddenly uninitialized.
    if ([aKey isEqualToString:@"position"]) {
        CABasicAnimation *anim = [CABasicAnimation animationWithKeyPath:@"position"]; 
        anim.duration = 0.01f; 
        return anim;
    } else {
        return [super defaultActionForKey:aKey];
    }
}

@end
