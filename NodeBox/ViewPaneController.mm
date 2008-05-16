//
//  ViewPaneController.m
//  switcher
//
//  Created by Frederik on 15/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "ViewPaneController.h"
#import "NetworkViewController.h"
#import "ParameterViewController.h"
#import "CanvasViewController.h"

@implementation ViewPaneController

- (id)init
{
    if (![NSBundle loadNibNamed:@"ViewPane" owner:self]) {
        NSLog(@"Could not load nib ViewPane");
    }
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
            [viewPane replaceSubview:contentView with:[_viewController view]];
            contentView = [_viewController view];
            [viewTypePopup selectItemWithTag:type];
            break;
        case ParameterViewType:
            NSLog(@"Switching to parameter view");
            _viewController = [[ParameterViewController alloc] init];
            [viewPane replaceSubview:contentView with:[_viewController view]];
            contentView = [_viewController view];
            [viewTypePopup selectItemWithTag:type];
            break;
        case CanvasViewType:
            NSLog(@"Switching to canvas view");
            _viewController = [[CanvasViewController alloc] init];
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
