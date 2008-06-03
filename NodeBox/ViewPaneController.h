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

enum ViewType {
    NoViewType = 0,
    NetworkViewType = 1,
    ParameterViewType = 2,
    CanvasViewType = 3
};

@class NodeBoxWindowController;
@class ViewController;

@interface ViewPaneController : NSObject {
    IBOutlet NSPopUpButton *viewTypePopup;
    IBOutlet NSButton *splitButton;
    IBOutlet NSView *viewPane;
    IBOutlet NSView *contentView;
    enum ViewType _type;
    NodeBoxWindowController *_windowController;
    ViewController *_viewController;
}

- (id)initWithWindowController:(NodeBoxWindowController *)windowController;
- (NSView *)viewPane;
- (enum ViewType)viewType;
- (void)setViewType:(enum ViewType)type;
- (void)switchType:(id)sender;
- (NodeBoxWindowController *)windowController;
- (void)setWindowController:(NodeBoxWindowController *)windowController;
- (ViewController *)viewController;

@end
