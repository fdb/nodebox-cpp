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
#import "NXParameterBox.h"

//static NSFont *kSmallFont = [NSFont fontWithName:@"LucidaGrande-Bold" size:10];

@interface ParameterViewController(Private)

- (void)setValueForControls;
- (void)removeControls;
- (void)rebuildControls;
- (NXParameterBox*)addBoxForParameter:(NodeCore::Parameter *)parameter y:(float)y index:(int)index;
- (void)addLabelForParameter:(NodeCore::Parameter *)parameter y:(float)y index:(int)index toBox:(NXParameterBox *)box;
- (NXDragControl *)addFloatControlForParameter:(NodeCore::Parameter *)parameter y:(float)y index:(int)index toBox:(NXParameterBox *)box;
- (void)floatValueChanged:(id)sender;

@end

@implementation ParameterViewController

- (id)initWithWindowController:(NodeBoxWindowController *)windowController
{
    self = [super initWithWindowController:windowController];
    if (![NSBundle loadNibNamed:@"ParameterView" owner:self]) {
        NSLog(@"Could not load nib ParameterView");
    }
    _controlMap = [[NSMutableDictionary alloc] init];
    [self rebuildControls];
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
    [self setValueForControls];
}


@end

@implementation ParameterViewController(Private)

#pragma mark Control interface

- (void)setValueForControls
{
    if (![self activeNode]) return;
    NodeCore::ParameterList parameters = [self activeNode]->getParameters();
    for (NodeCore::ParameterIterator iter = parameters.begin(); iter != parameters.end(); ++iter) {
        NodeCore::Parameter *parameter = *iter;
        NSString *parameterName = [NSString stringWithUTF8String:parameter->getName().c_str()];
        NSControl *control = [_controlMap objectForKey:parameterName];
        if (!control) break;
        if ([control floatValue] != parameter->asFloat()) {
            [control setFloatValue:parameter->asFloat()];
        }
    }
}

- (void)removeControls
{
    while ([[_view subviews] count] > 0) {
        NSView *subview = (NSView *)[[_view subviews] objectAtIndex:0];
        [subview removeFromSuperview];
    }
    [_controlMap removeAllObjects];
}

- (void)rebuildControls
{
    [self removeControls];
    if (![self activeNode]) return;
    NSRect frame = [_view frame];
    float y = frame.size.height - 24;
    int index = 0;
    NodeCore::ParameterList parameters = [self activeNode]->getParameters();
    for (NodeCore::ParameterIterator iter = parameters.begin(); iter != parameters.end(); ++iter) {
        NodeCore::Parameter *parameter = *iter;
        NSString *parameterName = [NSString stringWithUTF8String:parameter->getName().c_str()];
        if (parameter->getType() == NodeCore::kFloat) {
            NXParameterBox *parameterBox = [self addBoxForParameter:parameter y:y index:index];
            [self addLabelForParameter:parameter y:y index:index toBox:parameterBox];
            NSControl *control = [self addFloatControlForParameter:parameter y:y index:index toBox:parameterBox];
            [_controlMap setObject:control forKey:parameterName];
            y -= 24;
        } else {
            NSLog(@"Parameter: %s: don't know how to handle type %s", parameter->getName().c_str(), parameter->getType().c_str());
        }
        index++;
    }
}

- (NXParameterBox*)addBoxForParameter:(NodeCore::Parameter *)parameter y:(float)y index:(int)index
{
    NSRect parameterBoxRect = NSMakeRect(0, y, [_view frame].size.width, 24);
    NXParameterBox *parameterBox = [[NXParameterBox alloc] initWithFrame:parameterBoxRect];
    [parameterBox setAutoresizingMask:NSViewWidthSizable |NSViewMinYMargin];
    [_view addSubview:parameterBox];
    return parameterBox;
}

- (void)addLabelForParameter:(NodeCore::Parameter *)parameter y:(float)y index:(int)index toBox:(NXParameterBox *)box
{
    NSTextField *label = [[NSTextField alloc] init];
    [label setFrame:NSMakeRect(0, 4, 80, 15)];
    [label setStringValue:[NSString stringWithUTF8String:parameter->getName().c_str()]];
    [label setAlignment:NSRightTextAlignment];
    [label setEditable:FALSE];
    [label setBordered:FALSE];
    [label setDrawsBackground:FALSE];
    [label setFont:[NSFont fontWithName:@"LucidaGrande-Bold" size:10]];
    [box addSubview:label];
}


- (NXDragControl *)addFloatControlForParameter:(NodeCore::Parameter *)parameter y:(float)y index:(int)index toBox:(NXParameterBox *)box
{
    NXDragControl *control = [[NXDragControl alloc] init];
    [control setFrame:NSMakeRect(108, 4, 70, 15)];
    [control setFloatValue:parameter->asFloat()];
    [control setTarget:self];
    [control setTag:index];
    [control setAction:@selector(floatValueChanged:)];
    [box addSubview:control];
    return control;
}

#pragma mark Action callbacks

- (void)floatValueChanged:(id)sender
{
    int index = [sender tag];
    NodeCore::Parameter *parameter = [self activeNode]->getParameters()[index];
    [[self windowController] setFloat:[sender floatValue] forParameter:parameter];
}

@end