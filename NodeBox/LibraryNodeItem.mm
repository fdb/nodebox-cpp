//
//  CollectionViewNodeItem.mm
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "LibraryNodeItem.h"
#import "LibraryNodeView.h"

@implementation LibraryNodeItem

- (void)setSelected:(BOOL)flag
{
    [super setSelected:flag];
    LibraryNodeView *view = (LibraryNodeView* )[self view];
    [view setSelected:flag];
    [view setNeedsDisplay:YES];
}

- (void)setRepresentedObject:(id)object
{
    NSLog(@"Represented object %@", object);
    [super setRepresentedObject:object];
    LibraryNodeView *view = (LibraryNodeView* )[self view];
    [view setDescription:[object description]];
}

@end
