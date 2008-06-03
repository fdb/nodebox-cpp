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
 
#import "ViewPaneController.h"
#import "NetworkViewController.h"
#import "ParameterViewController.h"
#import "CanvasViewController.h"

@implementation ViewPaneController

- (id)initWithWindowController:(NodeBoxWindowController *)windowController
{
    if (![NSBundle loadNibNamed:@"ViewPane" owner:self]) {
        NSLog(@"Could not load nib ViewPane");
    }
    _windowController = windowController;
    return self;
}

- (enum ViewType)viewType
{
    return _type;
}

- (NSView *)viewPane
{
    return viewPane;
}

- (void)setViewType:(enum ViewType)type
{
    if (_viewController)
        [_viewController release];
    switch (type) {
        case NetworkViewType:
            NSLog(@"Switching to network view");
            _viewController = [[NetworkViewController alloc] init];
            [_viewController setWindowController:_windowController];
            [[_viewController view] setFrame:[contentView frame]];
            [viewPane replaceSubview:contentView with:[_viewController view]];
            contentView = [_viewController view];
            [viewTypePopup selectItemWithTag:type];
            break;
        case ParameterViewType:
            NSLog(@"Switching to parameter view");
            _viewController = [[ParameterViewController alloc] init];
            [_viewController setWindowController:_windowController];
            [[_viewController view] setFrame:[contentView frame]];
            [viewPane replaceSubview:contentView with:[_viewController view]];
            contentView = [_viewController view];
            [viewTypePopup selectItemWithTag:type];
            break;
        case CanvasViewType:
            NSLog(@"Switching to canvas view");
            _viewController = [[CanvasViewController alloc] init];
            [_viewController setWindowController:_windowController];
            [[_viewController view] setFrame:[contentView frame]];
            [viewPane replaceSubview:contentView with:[_viewController view]];
            contentView = [_viewController view];
            [viewTypePopup selectItemWithTag:type];
            break;
        default:
            NSLog(@"Switching to default view");
            // TODO: This empty view will leak.
            NSView *emptyView = [[NSView alloc] init];
            _viewController = NULL;
            [viewPane replaceSubview:contentView with:emptyView];
            contentView = emptyView;
            [viewTypePopup selectItemWithTag:type];
            break;
    }
}

- (void)switchType:(id)sender
{
    [self setViewType: (enum ViewType)[[sender selectedItem] tag]];
}

- (NodeBoxWindowController *)windowController
{
    return _windowController;
}

- (void)setWindowController:(NodeBoxWindowController *)windowController
{
    _windowController = windowController;
    if (_viewController) {
        [_viewController setWindowController:windowController];
    }
}

- (ViewController *)viewController
{
    return _viewController;
}

@end
