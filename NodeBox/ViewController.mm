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

@interface ViewController(Private)

- (void) setNeedsDisplay;

@end

@implementation ViewController

- (id)initWithWindowController:(NodeBoxWindowController *)windowController
{
    self = [super init];
    _windowController = windowController;
    return self;
}

#pragma mark State

- (NSView *)view
{
    return NULL;
}

- (NodeBoxWindowController *)windowController
{
    return _windowController;
}

- (NodeCore::Network *)rootNetwork
{
    return [_windowController rootNetwork];
}

- (NodeCore::Network *)activeNetwork
{
    return [_windowController activeNetwork];
}

- (NodeCore::Node *)activeNode
{
    return [_windowController activeNode];
}

- (NodeCore::Node *)renderedNode
{
    return [_windowController renderedNode];
}

#pragma mark Network notifications

- (void) didAddNode: (NodeCore::Node *)node
{
    [self setNeedsDisplay];
}

- (void) didRemoveNode: (NodeCore::Node *)node
{
    [self setNeedsDisplay];
}

- (void) didMoveNode: (NodeCore::Node *)node to: (NSPoint)pt
{
    [self setNeedsDisplay];
}

- (void) didModifyNode: (NodeCore::Node *)node
{
    [self setNeedsDisplay];
}

- (void) didConnect: (NodeCore::Field*)field to: (NodeCore::Node*)node
{
    [self setNeedsDisplay];
}

- (void) didChangeActiveNetwork: (NodeCore::Network *)activeNetwork
{
    [self setNeedsDisplay];
}

- (void) didChangeActiveNode: (NodeCore::Node *)activeNode
{
    [self setNeedsDisplay];
}

- (void) didChangeRenderedNode: (NodeCore::Node *)renderedNode
{
    [self setNeedsDisplay];
}

@end

@implementation ViewController(Private)

- (void) setNeedsDisplay
{
    if (NSView *v = [self view]) {
        [v setNeedsDisplay:TRUE];
    }
}

@end
