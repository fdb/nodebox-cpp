//
//  NodeBoxWindowController.m
//  NodeBox
//
//  Created by Frederik on 08/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "NodeBoxWindowController.h"
#import "NodeBoxDocument.h"

@implementation NodeBoxWindowController

- (id)init
{
    self = [super initWithWindowNibName:@"NodeBoxDocument"];
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
    NSLog(@"windowDidLoad");
    [networkView setDocument:(NodeBoxDocument *)[self document]];
    [networkPath setURL:[[NSURL alloc] initWithString:@"doc://doc/root/test/hello"]];
}

- (IBAction)createNode:(id)sender
{
    NodeBoxDocument *doc = (NodeBoxDocument *) [self document];
    [doc createNode];
}

- (IBAction)pathChanged:(id)sender
{
    NSLog(@"path changed %@", sender);
    NSLog(@"path %@", [networkPath objectValue]);
    NSLog(@"cell %@", [[networkPath clickedPathComponentCell] URL]);
    NSLog(@"relative path %@", [[[networkPath clickedPathComponentCell] URL] relativePath]);
}

@end
