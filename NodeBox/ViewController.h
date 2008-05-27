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
- (NodeCore::Node *)renderedNode;
- (void)setRenderedNode:(NodeCore::Node *)renderedNode;
- (void)activeNodeChanged;
- (void)renderedNodeChanged;
- (void)activeNetworkModified;

@end
