//
//  NodeBoxAppDelegate.mm
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "NodeBoxAppDelegate.h"
#import "LibraryPanelController.h"

@implementation NodeBoxAppDelegate

- (id)init
{ 
    self = [super init];
    libraryPanelController = [[LibraryPanelController alloc] init];
    [self showLibraryPanel:NULL];
    return self;
}

- (IBAction)showLibraryPanel:(id)sender
{
    [libraryPanelController showPanel:sender];
}

@end
