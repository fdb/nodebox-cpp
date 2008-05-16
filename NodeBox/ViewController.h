//
//  ViewController.h
//  switcher
//
//  Created by Frederik on 15/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <NodeCore/NodeCore.h>

@interface ViewController : NSObject {
    NodeCore::Network *_rootNetwork;
    NodeCore::Network *_activeNetwork;
    NodeCore::Node *_activeNode;
}

- (NSView *)view;
- (NodeCore::Network *)rootNetwork;
- (void)setRootNetwork:(NodeCore::Network *)network;
- (NodeCore::Network *)activeNetwork;
- (void)setActiveNetwork:(NodeCore::Network *)activeNetwork;
- (NodeCore::Node *)activeNode;
- (void)setActiveNode:(NodeCore::Node *)node;

@end
