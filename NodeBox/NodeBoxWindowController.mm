//
//  NodeBoxWindowController.m
//  NodeBox
//
//  Created by Frederik on 08/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "NodeBoxWindowController.h"
#import "NodeBoxDocument.h"
#import "ViewPaneController.h"

@implementation NodeBoxWindowController

- (id)init
{
    self = [super initWithWindowNibName:@"NodeBoxDocument"];
    viewPaneControllers = [[NSMutableArray alloc] init];
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    NSLog(@"windowDidLoad %@", [[self window] contentView]);
    // This will normally be set up from a config file with a layout.
    NSView *contentView = [[self window] contentView];
    NSSplitView *splitView = [[NSSplitView alloc] initWithFrame:[contentView bounds]];
    [splitView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    [splitView setVertical:TRUE];
    [contentView addSubview:splitView];
    ViewPaneController *c1 = [[ViewPaneController alloc] init];
    ViewPaneController *c2 = [[ViewPaneController alloc] init];
    [viewPaneControllers addObject:c1];
    [viewPaneControllers addObject:c2];
    [c1 setViewType:NetworkViewType];
    [c2 setViewType:ParameterViewType];
    [splitView addSubview:[c1 viewPane]];
    [splitView addSubview:[c2 viewPane]];
    [self setActiveNetwork:[(NodeBoxDocument *)[self document] rootNetwork]];
    //[networkView setDocument:(NodeBoxDocument *)[self document]];
    //[networkPath setURL:[[NSURL alloc] initWithString:@"doc://doc/root/test/hello"]];
}

- (IBAction)createNode:(id)sender
{
    NodeBoxDocument *doc = (NodeBoxDocument *) [self document];
    [doc createNode];
}

- (IBAction)pathChanged:(id)sender
{
    //NSLog(@"path changed %@", sender);
    //NSLog(@"path %@", [networkPath objectValue]);
    //NSLog(@"cell %@", [[networkPath clickedPathComponentCell] URL]);
    //NSLog(@"relative path %@", [[[networkPath clickedPathComponentCell] URL] relativePath]);
}

- (NodeCore::Network *)rootNetwork
{
    return [[self document] rootNetwork];
}

- (NodeCore::Network *)activeNetwork
{
    return _activeNetwork;
}

- (void)setActiveNetwork:(NodeCore::Network *)activeNetwork
{
    // TODO: Assert that active network is in root network.
    _activeNetwork = activeNetwork;
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] setActiveNetwork:activeNetwork];
    }
}

- (NodeCore::Node *)activeNode
{
    return _activeNode;
}

- (void)setActiveNode:(NodeCore::Node *)activeNode
{
    _activeNode = activeNode;
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] setActiveNode:activeNode];
    }
}


@end
