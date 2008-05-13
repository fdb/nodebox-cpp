//
//  NodeBoxAppDelegate.h
//  NodeBox
//
//  Created by Frederik on 13/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class LibraryPanelController;

@interface NodeBoxAppDelegate : NSObject {
    LibraryPanelController *libraryPanelController;
}

- (IBAction)showLibraryPanel:(id)sender;

@end
