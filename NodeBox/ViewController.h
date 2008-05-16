//
//  ViewController.h
//  switcher
//
//  Created by Frederik on 15/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <NodeCore/NodeCore.h>

@class NodeBoxWindowController;

@interface ViewController : NSObject {
    NodeBoxWindowController *_windowController;
}

- (NSView *)view;
- (NodeBoxWindowController *)windowController;
- (void)setWindowController:(NodeBoxWindowController *)windowController;
- (NodeCore::Network *)rootNetwork;
- (NodeCore::Network *)activeNetwork;
- (void)setActiveNetwork:(NodeCore::Network *)activeNetwork;
- (void)activeNetworkChanged;
- (NodeCore::Node *)activeNode;
- (void)setActiveNode:(NodeCore::Node *)activeNode;
- (void)activeNodeChanged;
- (void)activeNetworkModified;

@end
