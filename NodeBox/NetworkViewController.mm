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
 
#import <NodeCore/NodeCore.h>
#import "NetworkViewController.h"
#import "NetworkView.h"
#import "NodeBoxWindowController.h"

@implementation NetworkViewController

- (id)initWithWindowController:(NodeBoxWindowController *)windowController
{
    self = [super initWithWindowController:windowController];
    if (![NSBundle loadNibNamed:@"NetworkView" owner:self]) {
        NSLog(@"Could not load nib NetworkView");
    }
    [(NetworkView *)_view setController:self];
    return self;
}

- (NSView *)view
{
    return _view;
}

#pragma Network notifications

- (void) didAddNode: (NodeCore::Node *)node
{
    [_view addLayerForNode:node];
    [_view redrawConnections];
}

- (void) didRemoveNode: (NodeCore::Node *)node
{
    [_view removeLayerForNode:node];
    [_view redrawConnections];
}

- (void) didMoveNode: (NodeCore::Node *)node to: (NSPoint)pt
{
    [_view moveNode:node to:pt];
    [_view redrawConnections];
}

- (void) didConnect: (NodeCore::Field*)field to: (NodeCore::Node*)node
{
    [_view redrawConnections];
}

- (void) didChangeActiveNetwork: (NodeCore::Network *)activeNetwork
{
    [_view rebuildNetwork];
}

- (void) didChangeActiveNode: (NodeCore::Node *)activeNode
{
    [_view deselect];
    [_view select:activeNode];
}

- (void) didChangeRenderedNode: (NodeCore::Node *)renderedNode
{
    // TODO: make indicator for rendered node.
}

#pragma Context menu

- (void)contextMenuForNode:(NodeCore::Node *)node event:(NSEvent *)theEvent
{
    _contextNode = node;
    [NSMenu popUpContextMenu:nodeContextMenu withEvent:theEvent forView:[self view]];   
}

- (void)deleteNode:(id)sender
{
    if (!_contextNode) return;
    [[self windowController] removeNode:_contextNode];
}

- (void)renameNode:(id)sender
{
    // TODO: implement
}

@end
