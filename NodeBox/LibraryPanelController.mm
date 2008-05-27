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
 
#import "LibraryPanelController.h"
#import "NodeInfoWrapper.h"

@implementation LibraryPanelController

- (id)init
{
    self = [super initWithWindowNibName:@"LibraryPanel"];
    NSString *plugInsPath = [[NSBundle mainBundle] builtInPlugInsPath];
    nodeLibraryManager = new NodeCore::NodeLibraryManager([plugInsPath UTF8String]);
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