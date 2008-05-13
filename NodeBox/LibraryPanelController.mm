//
//  LibraryPanelController.mm
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "LibraryPanelController.h"


@implementation LibraryPanelController

- (id)init
{
    self = [super initWithWindowNibName:@"LibraryPanel"];
    rootItems = [[NSMutableArray alloc] init];
    [rootItems addObject:@"Library"];
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    NSLog(@"LPC: windowDidLoad");    
    [treeView setDataSource:self];
    NSMutableArray *arr = [[NSMutableArray alloc] init];
    [arr addObject:@"Test Node"];
    [arr addObject:@"Another Node"];
    [collectionView setContent:arr];
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