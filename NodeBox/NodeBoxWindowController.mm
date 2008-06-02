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
#import "NodeBoxAppDelegate.h"

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
    NSSplitView *primarySplit = [[NSSplitView alloc] initWithFrame:[contentView bounds]];
    [primarySplit setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    [primarySplit setVertical:TRUE];
    [contentView addSubview:primarySplit];
    NSSplitView *secondarySplit = [[NSSplitView alloc] initWithFrame:[contentView bounds]];
    [secondarySplit setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    [secondarySplit setVertical:FALSE];
    ViewPaneController *canvasView = [[ViewPaneController alloc] initWithWindowController:self];
    ViewPaneController *parameterView = [[ViewPaneController alloc] initWithWindowController:self];
    ViewPaneController *networkView = [[ViewPaneController alloc] initWithWindowController:self];
    [viewPaneControllers addObject:canvasView];
    [viewPaneControllers addObject:parameterView];
    [viewPaneControllers addObject:networkView];
    [canvasView setViewType:CanvasViewType];
    [parameterView setViewType:ParameterViewType];
    [networkView setViewType:NetworkViewType];
    [primarySplit addSubview:[canvasView viewPane]];
    [primarySplit addSubview:secondarySplit];
    [secondarySplit addSubview:[parameterView viewPane]];
    [secondarySplit addSubview:[networkView viewPane]];
    [self setActiveNetwork:[(NodeBoxDocument *)[self document] rootNetwork]];
    //[networkView setDocument:(NodeBoxDocument *)[self document]];
    //[networkPath setURL:[[NSURL alloc] initWithString:@"doc://doc/root/test/hello"]];
}

#pragma mark Network operations

-(NodeCore::Node*) createNode:(NodeCore::NodeInfo *)info at:(NSPoint)point
{
    NSLog(@"Create node %s at %f, %f", info->getName().c_str(), point.x, point.y);
    NodeCore::Node *node = info->create();
    node->setX(point.x);
    node->setY(point.y);
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Create Node"];
    }
    [self activeNetwork]->setUniqueNodeName(node);
    [self activeNetwork]->add(node);

    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didAddNode:node];
    }

    return node;    
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

    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didAddNode:node];
    }

    return node;
}

-(void) addNode:(NodeCore::Node*) node
{
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Add Node"];
    }

    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didAddNode:node];
    }
}

- (BOOL) removeNode:(NodeCore::Node *)node
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
    
    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didRemoveNode:node];
    }

    // Not deleting the node, since the undoManager needs it.
    return true;
}

- (void) moveNode: (NodeCore::Node *)node to: (NSPoint)pt;
{
    node->setX(pt.x);
    node->setY(pt.y);
    
    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didMoveNode:node to:pt];
    }
}

- (void) setFloat: (float)value forField: (NodeCore::Field*)field
{
    field->set(value);

    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didModifyNode:field->getNode()];
    }    
}

- (void) connectFrom: (NodeCore::Field*)field to: (NodeCore::Node*)node
{
    field->connect(node);

    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didConnect:field to:node];
    }
}


- (void)setActiveNetwork:(NodeCore::Network *)activeNetwork
{
    if (_activeNetwork == activeNetwork) return;
    const char *c_name = activeNetwork->getName().c_str();
    NSLog(@"setting active network to %s", c_name);
    // TODO: Assert that active network is in the root network.
    _activeNetwork = activeNetwork;

    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didChangeActiveNetwork:activeNetwork];
    }
}

- (void)setActiveNode:(NodeCore::Node *)activeNode
{
    if (_activeNode == activeNode) return;
    _activeNode = activeNode;

    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didChangeActiveNode:activeNode];
    }
}

- (void)setRenderedNode:(NodeCore::Node *)renderedNode
{
    if (self.renderedNode == renderedNode) return;
    if (renderedNode != NULL) {
        NSLog(@"Setting rendered node to %s", renderedNode->getName().c_str());
    } else {
        NSLog(@"Setting rendered node to null"  );
    }
    if (!_activeNetwork) return;
    _activeNetwork->setRenderedNode(renderedNode);

    // Notify
    NSEnumerator *enumerator = [viewPaneControllers objectEnumerator];
    ViewPaneController *c;
    while (c = [enumerator nextObject]) {
        [[c viewController] didChangeRenderedNode:renderedNode];
    }
}

#pragma mark State

- (NodeCore::Network *)rootNetwork
{
    return [[self document] rootNetwork];
}

- (NodeCore::Network *)activeNetwork
{
    return _activeNetwork;
}

- (NodeCore::Node *)activeNode
{
    return _activeNode;
}

- (NodeCore::Node *)renderedNode
{
    if (!_activeNetwork) return NULL;
    return _activeNetwork->getRenderedNode();
}

#pragma mark Library

- (NodeCore::NodeLibraryManager*)nodeLibraryManager
{
    NodeBoxAppDelegate *delegate = [[NSApplication sharedApplication] delegate];
    return [delegate nodeLibraryManager];
}

- (IBAction)pathChanged:(id)sender
{
    //NSLog(@"path changed %@", sender);
    //NSLog(@"path %@", [networkPath objectValue]);
    //NSLog(@"cell %@", [[networkPath clickedPathComponentCell] URL]);
    //NSLog(@"relative path %@", [[[networkPath clickedPathComponentCell] URL] relativePath]);
}

@end
