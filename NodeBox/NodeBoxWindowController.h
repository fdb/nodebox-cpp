//
//  NodeBoxWindowController.h
//  NodeBox
//
//  Created by Frederik on 08/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NetworkView;

@interface NodeBoxWindowController : NSWindowController
{
    NSMutableArray *paneWrappers;
}

- (IBAction)createNode:(id)sender;
- (IBAction)pathChanged:(id)sender;

@end
