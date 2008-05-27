//
//  LibraryPanelController.h
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <NodeCore/NodeCore.h>

@interface LibraryPanelController : NSWindowController {
    NodeCore::NodeLibraryManager *nodeLibraryManager;
    NSMutableArray *rootItems;
    IBOutlet NSOutlineView *treeView;
    IBOutlet NSCollectionView *collectionView;
    IBOutlet NSArrayController *nodeInfoController;
}
- (IBAction)showPanel:(id)sender;
@end
