//
//  PaneWrapperController.m
//  switcher
//
//  Created by Frederik on 15/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "PaneWrapperController.h"
#import "NetworkViewController.h"
#import "ParameterViewController.h"
#import "CanvasViewController.h"

@implementation PaneWrapperController

- (id)init
{
    if (![NSBundle loadNibNamed:@"PaneWrapper" owner:self]) {
        NSLog(@"Could not load nib PaneWrapper");
    }
    NSLog(@"Content view %@", contentView);
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
    if (_controller)
        [_controller release];
    switch (type) {
        case NetworkViewType:
            NSLog(@"Switching to network view");
            _controller = [[NetworkViewController alloc] init];
            [viewPane replaceSubview:contentView with:[_controller view]];
            contentView = [_controller view];
            break;
        case ParameterViewType:
            NSLog(@"Switching to parameter view");
            _controller = [[ParameterViewController alloc] init];
            [viewPane replaceSubview:contentView with:[_controller view]];
            contentView = [_controller view];
            break;
        case CanvasViewType:
            NSLog(@"Switching to canvas view");
            _controller = [[CanvasViewController alloc] init];
            [viewPane replaceSubview:contentView with:[_controller view]];
            contentView = [_controller view];
            break;
        default:
            NSLog(@"Switching to default view");
            // TODO: This empty view will leak.
            NSView *emptyView = [[NSView alloc] init];
            _controller = NULL;
            [viewPane replaceSubview:contentView with:emptyView];
            contentView = emptyView;
            break;
    }
}

- (void)switchType:(id)sender
{
    [self setViewType: (enum ViewType)[[sender selectedItem] tag]];
}

@end
