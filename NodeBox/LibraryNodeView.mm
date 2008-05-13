//
//  CollectionViewNodeView.mm
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "LibraryNodeView.h"


@implementation LibraryNodeView

- (void)setSelected:(BOOL)flag
{
  selected = flag;
}

- (BOOL)selected
{
  return selected;
}

- (void)awakeFromNib
{
    NSLog(@"LibraryNodeView awoke from nib");
}

- (void)drawRect:(NSRect)rect
{
    if (selected) {
        [[NSColor selectedControlColor] set];
        NSRectFill([self bounds]);    
    }
    [super drawRect:rect];
}

- (void)setDescription:(NSString*)description
{
    NSLog(@"setting description to %@ %@", description, myLabel);
    [myLabel setTitleWithMnemonic:description];
}

@end
