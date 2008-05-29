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
#import <Cocoa/Cocoa.h>
#import "ViewController.h"
#import "NetworkView.h"

@interface NodeWrapper : NSObject {
    NodeCore::Node *_theNode;
}
- (id)initWithNode:(NodeCore::Node *)node;
- (NodeCore::Node*)node;
@end

@interface FieldWrapper : NSObject {
    NodeCore::Field *_field;
}
- (id)initWithField:(NodeCore::Field *)field;
- (NodeCore::Field*)field;
@end

@interface NetworkViewController : ViewController {
    IBOutlet NetworkView *_view;
    IBOutlet NSMenu *nodeContextMenu;
    NodeCore::Node *_contextNode;
}

- (id)initWithWindowController:(NodeBoxWindowController *)windowController;
- (NSView *)view;
- (void)contextMenuForNode:(NodeCore::Node *)node event:(NSEvent *)theEvent;
- (void)deleteNode:(id)sender;
- (void)renameNode:(id)sender;

@end
