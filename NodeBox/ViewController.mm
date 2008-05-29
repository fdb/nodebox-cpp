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
 
#import "ViewController.h"
#import "NodeBoxWindowController.h"

@implementation ViewController

- (id)initWithWindowController:(NodeBoxWindowController *)windowController
{
    self = [super init];
    _windowController = windowController;
    return self;
}

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

- (NodeCore::Node *)renderedNode
{
    return [_windowController renderedNode];
}

- (void)setRenderedNode:(NodeCore::Node *)renderedNode
{
    [_windowController setRenderedNode:renderedNode];
}

- (void)activeNodeChanged:(NodeCore::Node *)activeNode;
{
    if (NSView *v = [self view]) {
        [v setNeedsDisplay:TRUE];
    }
}

- (void)activeNetworkModified;
{
    if (NSView *v = [self view]) {
        [v setNeedsDisplay:TRUE];
    }
}

- (void)renderedNodeChanged:(NodeCore::Node *)renderedNode;
{
    if (NSView *v = [self view]) {
        [v setNeedsDisplay:TRUE];
    }
}

@end
