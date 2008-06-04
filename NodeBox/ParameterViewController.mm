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
 
#import "ParameterViewController.h"
#import "NodeBoxWindowController.h"
#import "NXDragControl.h"

//static NSFont *kSmallFont = [NSFont fontWithName:@"LucidaGrande-Bold" size:10];

@interface ParameterViewController(Private)

- (void)removeControls;
- (void)rebuildControls;
- (void)addLabelForField:(NodeCore::Field *)field y:(float)y index:(int)index;
- (void)addFloatControlForField:(NodeCore::Field *)field y:(float)y index:(int)index;
- (void)floatValueChanged:(id)sender;

@end

@implementation ParameterViewController

- (id)initWithWindowController:(NodeBoxWindowController *)windowController
{
    self = [super initWithWindowController:windowController];
    if (![NSBundle loadNibNamed:@"ParameterView" owner:self]) {
        NSLog(@"Could not load nib ParameterView");
    }
    // Perhaps construct view?
    return self;
}

- (NSView *)view
{
    return _view;
}

#pragma mark Network notifications

- (void) didChangeActiveNode: (NodeCore::Node *)activeNode
{
    [self rebuildControls];
}

- (void) didModifyNode: (NodeCore::Node *)node
{
    [self rebuildControls];
}


@end

@implementation ParameterViewController(Private)

#pragma mark Action callbacks

- (void)removeControls
{
    while ([[_view subviews] count] > 0) {
        NSView *subview = (NSView *)[[_view subviews] objectAtIndex:0];
        [subview removeFromSuperview];
    }
}

- (void)rebuildControls
{
    [self removeControls];
    if (![self activeNode]) return;
    NSRect frame = [_view frame];
    float y = frame.size.height - 20;
    int index = 0;
    NodeCore::FieldList fields = [self activeNode]->getFields();
    for (NodeCore::FieldIterator iter = fields.begin(); iter != fields.end(); ++iter) {
        NodeCore::Field *field = *iter;
        if (field->getType() == NodeCore::kFloat) {
            [self addLabelForField:field y:y index:index];
            [self addFloatControlForField:field y:y index:index];
        } else {
            NSLog(@"Field: %s: don't know how to handle type %s", field->getName().c_str(), field->getType().c_str());
        }
        y -= 21;
        index++;
    }
}

- (void)addLabelForField:(NodeCore::Field *)field y:(float)y index:(int)index
{
    NSTextField *label = [[NSTextField alloc] init];
    [label setFrame:NSMakeRect(0, y, 100, 15)];
    [label setStringValue:[NSString stringWithUTF8String:field->getName().c_str()]];
    [label setAlignment:NSRightTextAlignment];
    [label setEditable:FALSE];
    [label setBordered:FALSE];
    [label setDrawsBackground:FALSE];
    [label setFont:[NSFont fontWithName:@"LucidaGrande-Bold" size:10]];
    [_view addSubview:label];
}


- (void)addFloatControlForField:(NodeCore::Field *)field y:(float)y index:(int)index
{
    NXDragControl *control = [[NXDragControl alloc] init];
    [control setFrame:NSMakeRect(108, y-1, 100, 15)];
    [control setFloatValue:field->asFloat()];
    [control setTarget:self];
    [control setTag:index];
    [control setAction:@selector(floatValueChanged:)];
    [_view addSubview:control];
}

- (void)floatValueChanged:(id)sender
{
    int index = [sender tag];
    NodeCore::Field *field = [self activeNode]->getFields()[index];
    [[self windowController] setFloat:[sender floatValue] forField:field];
}

@end