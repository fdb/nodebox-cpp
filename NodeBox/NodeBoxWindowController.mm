//
//  NodeBoxWindowController.m
//  NodeBox
//
//  Created by Frederik on 08/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "NodeBoxWindowController.h"
#import "NodeBoxDocument.h"
#import "PaneWrapperController.h"

@implementation NodeBoxWindowController

- (id)init
{
    self = [super initWithWindowNibName:@"NodeBoxDocument"];
    paneWrappers = [[NSMutableArray alloc] init];
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    NSLog(@"windowDidLoad %@", [[self window] contentView]);
    // This will normally be set up from a config file with a layout.
    NSView *contentView = [[self window] contentView];
    NSSplitView *splitView = [[NSSplitView alloc] initWithFrame:[contentView bounds]];
    [contentView addSubview:splitView];
    NSLog(@"split subs %@", [splitView subviews]);
    PaneWrapperController *c1 = [[PaneWrapperController alloc] init];
    PaneWrapperController *c2 = [[PaneWrapperController alloc] init];
    [splitView addSubview:[c1 paneWrapper]];
    [splitView addSubview:[c2 paneWrapper]];
    //[splitView replaceSubview:firstSplit with:[c1 paneWrapper]];
    //[splitView replaceSubview:secondSplit with:[c2 paneWrapper]];
    //[networkView setDocument:(NodeBoxDocument *)[self document]];
    //[networkPath setURL:[[NSURL alloc] initWithString:@"doc://doc/root/test/hello"]];
}

- (IBAction)createNode:(id)sender
{
    NodeBoxDocument *doc = (NodeBoxDocument *) [self document];
    [doc createNode];
}

- (IBAction)pathChanged:(id)sender
{
    //NSLog(@"path changed %@", sender);
    //NSLog(@"path %@", [networkPath objectValue]);
    //NSLog(@"cell %@", [[networkPath clickedPathComponentCell] URL]);
    //NSLog(@"relative path %@", [[[networkPath clickedPathComponentCell] URL] relativePath]);
}

@end
