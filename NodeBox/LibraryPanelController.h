//
//  LibraryPanelController.h
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface LibraryPanelController : NSWindowController {
    NSMutableArray *rootItems;
    IBOutlet NSOutlineView *treeView;
    IBOutlet NSCollectionView *collectionView;
}
- (IBAction)showPanel:(id)sender;
@end
