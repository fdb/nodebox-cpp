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

@class NetworkViewController;
class NetworkVisualiser;

enum DragModeType {
    kDragModeNotDragging = 0,
    kDragModeNode = 1,
    kDragModeConnect = 2
};

@interface NetworkView : NSView {
    IBOutlet NetworkViewController *viewController;
    NetworkVisualiser* visualiser;
    DragModeType _dragMode;
    NodeCore::Node *_draggingNode;
    NodeCore::Node *_dragOverNode;
    NSPoint _dragPoint;
    bool _startedDragging;
    NodeCore::Node *_deferredDraggingNode;
    NSPoint _clickPoint;
}

- (NetworkViewController*)controller;
- (void)setController:(NetworkViewController *)controller;

- (NodeCore::Node *)findNodeAt:(NSPoint) point;
- (void)_drawNode:(NodeCore::Node *)node;
- (void)_drawConnectionWithInputField:(NodeCore::Field *)input outputField:(NodeCore::Field *)output;
- (void)_drawConnectionLineFrom:(NSPoint)p1 to:(NSPoint)p2;
- (void)connectNodeToField:(NSMenuItem *)menuItem;
@end
