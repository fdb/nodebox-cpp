//
//  ViewController.m
//  switcher
//
//  Created by Frederik on 15/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"


@implementation ViewController

- (NSView *)view
{
return NULL;
}

- (NodeCore::Network *)rootNetwork
{
    return _rootNetwork;
}

- (void)setRootNetwork:(NodeCore::Network *)network
{
    _rootNetwork = network;
}

- (NodeCore::Network *)activeNetwork
{
    return _activeNetwork;
}

- (void)setActiveNetwork:(NodeCore::Network *)activeNetwork
{
    _activeNetwork = activeNetwork;
}

- (NodeCore::Node *)activeNode
{
    return _activeNode;
}

- (void)setActiveNode:(NodeCore::Node *)node
{
    _activeNode = node;
}

@end
