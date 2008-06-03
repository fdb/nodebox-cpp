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

@implementation NodeWrapper

- (id)initWithNode:(NodeCore::Node *)node
{
    self = [super init];
    _theNode = node;
    return self;
}

- (NodeCore::Node*)node
{
    return _theNode;
}

@end

@implementation FieldWrapper

- (id)initWithField:(NodeCore::Field *)field
{
    self = [super init];
    _field = field;
    return self;
}

- (NodeCore::Field*)field
{
    return _field;
}

@end

@implementation NetworkViewController

- (id)init
{
    self = [super init];
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
