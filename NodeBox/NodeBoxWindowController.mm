/*
 * This file is part of NodeBox.
 *
 * Copyright (C) 2008 Frederik De Bleser (frederik@pandora.be)
 *
 * NodeBox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NodeBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NodeBox.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#import "NodeBoxWindowController.h"
#import "NodeBoxDocument.h"
#import "ViewPaneController.h"
#import "ViewController.h"

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
    // This will normally be set up from a config file with a layout.
    NSView *contentView = [[self window] contentView];
    NSSplitView *splitView = [[NSSplitView alloc] initWithFrame:[contentView bounds]];
    [splitView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    [splitView setVertical:TRUE];
    [contentView addSubview:splitView];
    ViewPaneController *c1 = [[ViewPaneController alloc] initWithWindowController:self];
    ViewPaneController *c2 = [[ViewPaneController alloc] initWithWindowController:self];
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

-(NodeCore::Node*) createNode
{
    return [self createNodeAt:NSMakePoint(30, 30)];
}

-(NodeCore::Node*) createNodeAt:(NSPoint)point
{
    NSLog(@"Create node at %f, %f", point.x, point.y);
    NodeCore::Node *node = new NodeCore::Node();
    node->setX(point.x);
    node->setY(point.y);
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Create Node"];
    }
    [self activeNetwork]->setUniqueNodeName(node);
    [self activeNetwork]->add(node);
    [self activeNetworkModified];
    return node;
}

-(void) addNode:(NodeCore::Node*) node
{
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Add Node"];
    }
    [self activeNetwork]->add(node);
    [self activeNetworkModified];
}

-(BOOL) removeNode:(NodeCore::Node *)node
{
    if (node->getNetwork() != [self activeNetwork]) {
        return false;
    }
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Remove Node"];
    }
    [self activeNetwork]->remove(node);
    [self activeNetworkModified];
    // Not deleting the node, since the undoManager needs it.
    return true;
}

- (void) activeNetworkModified
{
    // Notify everybody
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] activeNetworkModified];
    }
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
    const char *c_name = activeNetwork->getName().c_str();
    NSLog(@"setting active network to %s", c_name);
    // TODO: Assert that active network is in the root network.
    _activeNetwork = activeNetwork;
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        NSLog(@"Active network in %@", c);
        [[c viewController] activeNetworkChanged];
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
        [[c viewController] activeNodeChanged];
    }
}

@end
