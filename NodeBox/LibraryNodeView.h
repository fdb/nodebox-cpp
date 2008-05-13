//
//  CollectionViewNodeView.h
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface LibraryNodeView : NSView {
    BOOL selected;
    IBOutlet NSTextField *myLabel;
}

- (void)setSelected:(BOOL)flag;
- (BOOL)selected;
- (void)setDescription:(NSString*)description;

@end
