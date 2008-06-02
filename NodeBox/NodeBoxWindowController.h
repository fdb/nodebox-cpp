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
 
#import <Cocoa/Cocoa.h>
#import <NodeCore/NodeCore.h>

@class NetworkView;

@interface NodeBoxWindowController : NSWindowController
{
    NSMutableArray *viewPaneControllers;
    NodeCore::Network *_activeNetwork;
    NodeCore::Node *_activeNode;
}

//// Network operations ////
- (NodeCore::Node*) createNode: (NodeCore::NodeInfo *)info at: (NSPoint)point;
- (NodeCore::Node*) createNodeAt: (NSPoint)point;
- (void) addNode: (NodeCore::Node *)node;
- (BOOL) removeNode: (NodeCore::Node *)node;
- (void) moveNode: (NodeCore::Node *)node to:(NSPoint)pt;
- (void) connectFrom: (NodeCore::Field*)field to: (NodeCore::Node*)node;
- (void) setActiveNetwork: (NodeCore::Network *)activeNetwork;
- (void) setActiveNode: (NodeCore::Node *)activeNode;
- (void) setRenderedNode: (NodeCore::Node *)renderedNode;

//// State ////
- (NodeCore::Network *) rootNetwork;
- (NodeCore::Network *) activeNetwork;
- (NodeCore::Node *) activeNode;
- (NodeCore::Node *) renderedNode;

//// Library ////
- (NodeCore::NodeLibraryManager*) nodeLibraryManager;

// TODO: remove
- (IBAction) pathChanged: (id)sender; // TODO should be renamed
@end
