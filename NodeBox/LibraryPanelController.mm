//
//  LibraryPanelController.mm
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "LibraryPanelController.h"
#import "NodeInfoWrapper.h"

@implementation LibraryPanelController

- (id)init
{
    self = [super initWithWindowNibName:@"LibraryPanel"];
    nodeLibraryManager = new NodeCore::NodeLibraryManager("/Users/fdb/Projects/nodebox2/NodeBox/build/Debug/NodeBox.app/Contents/PlugIns");
    rootItems = [[NSMutableArray alloc] init];
    [rootItems addObject:@"Library"];
    return self;
}

- (void)dealloc
{
    delete nodeLibraryManager;
    [super dealloc];
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    [treeView setDataSource:self];
    
    NodeCore::NodeLibraryList libs = nodeLibraryManager->libraries();
    for(NodeCore::NodeLibraryIterator libIter = libs.begin(); libIter != libs.end(); ++libIter) {
        NodeCore::NodeLibrary *lib = (*libIter);
        NSLog(@"Library %s", lib->getName().c_str());
        NodeCore::NodeInfoList nodeInfos = lib->getNodeInfoList();
        for (NodeCore::NodeInfoIterator nodeInfoIter = nodeInfos.begin(); nodeInfoIter != nodeInfos.end(); ++nodeInfoIter) {
            NodeCore::NodeInfo *nodeInfo = (*nodeInfoIter);
            NSLog(@"  Node %s", nodeInfo->getName().c_str());
            [nodeInfoController addObject:[[NodeInfoWrapper alloc] initWithNodeInfo:nodeInfo]];
        }
    }
}

- (void)windowDidBecomeKey:(NSNotification *)notification
{
    // We need to redraw the selected LibraryNodeViews.
    [collectionView setNeedsDisplay:TRUE];
}

- (void)windowDidResignKey:(NSNotification *)notification
{
    // We need to redraw the selected LibraryNodeViews.
    [collectionView setNeedsDisplay:TRUE];
}

- (IBAction)showPanel:(id)sender
{
    [[self window] makeKeyAndOrderFront:sender];
}

@end

@implementation LibraryPanelController (NSOutlineViewDataSource)

- (int) outlineView: (NSOutlineView *)outlineView numberOfChildrenOfItem: (id)item
{
   if (!item)
   {
      return [rootItems count];
   }
   
   return 0;

   //return [(PDFOutlineItem*)item countKids];
}


- (id) outlineView: (NSOutlineView *)outlineView child: (int)index ofItem: (id)item
{
   NSArray* items;

   if (!item)
   {
      items = rootItems;
   }
   else
   {
    return NULL;
      //items = [(PDFOutlineItem*)item kids];
   }

   return [items objectAtIndex: index];
}


- (BOOL) outlineView: (NSOutlineView *)outlineView isItemExpandable: (id)item
{
    return TRUE;
   //return ([(PDFOutlineItem*)item countKids] > 0);
}


- (id) outlineView: (NSOutlineView *)outlineView
objectValueForTableColumn: (NSTableColumn *)tableColumn
            byItem:(id)item
{
    return @"Library";
   // return [(PDFOutlineItem*)item title];
}

@end