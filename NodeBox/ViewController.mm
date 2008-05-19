//
//  ViewController.m
//  switcher
//
//  Created by Frederik on 15/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"
#import "NodeBoxWindowController.h"

@implementation ViewController

- (NSView *)view
{
    return NULL;
}

- (NodeBoxWindowController *)windowController
{
    return _windowController;
}

- (void)setWindowController:(NodeBoxWindowController *)windowController
{
    _windowController = windowController;
}

- (NodeCore::Network *)rootNetwork
{
    return [_windowController rootNetwork];
}

- (NodeCore::Network *)activeNetwork
{
    return [_windowController activeNetwork];
}

- (void)setActiveNetwork:(NodeCore::Network *)activeNetwork
{
    [_windowController setActiveNetwork:activeNetwork];
}

- (void)activeNetworkChanged
{
    if (NSView *v = [self view]) {
        [v setNeedsDisplay:TRUE];
    }
}

- (NodeCore::Node *)activeNode
{
    return [_windowController activeNode];
}

- (void)setActiveNode:(NodeCore::Node *)activeNode
{
    [_windowController setActiveNode:activeNode];
}

- (void)activeNodeChanged
{
    if (NSView *v = [self view]) {
        [v setNeedsDisplay:TRUE];
    }
}

- (void)activeNetworkModified
{
    if (NSView *v = [self view]) {
        [v setNeedsDisplay:TRUE];
    }
}

@end
