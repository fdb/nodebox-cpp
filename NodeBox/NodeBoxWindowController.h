//
//  NodeBoxWindowController.h
//  NodeBox
//
//  Created by Frederik on 08/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <NodeCore/NodeCore.h>

@class NetworkView;

@interface NodeBoxWindowController : NSWindowController
{
    NSMutableArray *viewPaneControllers;
    NodeCore::Network *_activeNetwork;
    NodeCore::Node *_activeNode;
}

-(NodeCore::Node*) createNode;
-(NodeCore::Node*) createNodeAt:(NSPoint)point;
-(void) addNode:(NodeCore::Node *)node;
-(BOOL) removeNode:(NodeCore::Node *)node;
- (void)activeNetworkModified; // TODO not the best name

- (IBAction)pathChanged:(id)sender; // TODO should be renamed
- (NodeCore::Network *)rootNetwork;
- (NodeCore::Network *)activeNetwork;
- (void)setActiveNetwork:(NodeCore::Network *)activeNetwork;
- (NodeCore::Node *)activeNode;
- (void)setActiveNode:(NodeCore::Node *)activeNode;

@end
