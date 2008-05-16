//
//  PaneWrapperController.h
//  switcher
//
//  Created by Frederik on 15/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

enum ViewType {
    NoViewType = 0,
    NetworkViewType = 1,
    ParameterViewType = 2,
    CanvasViewType = 3
};

@class ViewController;

@interface PaneWrapperController : NSObject {
    IBOutlet NSPopUpButton *viewTypePopup;
    IBOutlet NSButton *splitButton;
    IBOutlet NSView *viewPane;
    IBOutlet NSView *contentView;
    enum ViewType _type;
    ViewController *_controller;    
}

- (NSView *)viewPane;
- (enum ViewType)viewType;
- (void)setViewType:(enum ViewType)type;
- (void)switchType:(id)sender;

@end
