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

@implementation ParameterViewController

- (id)initWithWindowController:(NodeBoxWindowController *)windowController
{
    self = [super initWithWindowController:windowController];
    if (![NSBundle loadNibNamed:@"ParameterView" owner:self]) {
        NSLog(@"Could not load nib ParameterView");
    }
    return self;
}

- (NSView *)view
{
    return _view;
}

- (void)activeNodeChanged:(NodeCore::Node *)activeNode;
{
    [tableView reloadData];
}

@end

@implementation ParameterViewController (NSTableDataSource)

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView
{

    NSLog(@"numberOfRowsInTableView");
    if (![self activeNode]) return 0;
    NSLog(@"rowcount %i", [self activeNode]->getFields().size());
    return [self activeNode]->getFields().size();
}

- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(NSInteger)rowIndex
{
    if (![self activeNode]) return NULL;
    NodeCore::Field *field = [self activeNode]->getFields()[rowIndex];
    if ([[aTableColumn identifier] isEqualToString:@"name"]) {
        return [NSString stringWithCString:field->getName().c_str()];
    } else if ([[aTableColumn identifier] isEqualToString:@"value"]) {
        NSString *value;
        if (field->getType() == NodeCore::kInt) {
            value = [NSString stringWithFormat:@"%i", field->asInt()];
        } else if (field->getType() == NodeCore::kFloat) {
            value = [NSString stringWithFormat:@"%.3f", field->asFloat()];
        } else if (field->getType() == NodeCore::kString) {
            value = [NSString stringWithCString:field->asString().c_str()];
        } else {
            value = @"<object>";
        }
        return value;
    } else if ([[aTableColumn identifier] isEqualToString:@"stepper"]) {
        if (field->getType() == NodeCore::kInt) {
            return [NSNumber numberWithInt:field->asInt()];
        } else if (field->getType() == NodeCore::kFloat) {
            return [NSNumber numberWithFloat:field->asFloat()];
        } else {
            return 0;
        }
    } else {
        return @"invalid";
    }
}

- (void)tableView:(NSTableView *)aTableView setObjectValue:(id)objectValue forTableColumn:(NSTableColumn *)aTableColumn row:(NSInteger)rowIndex
{
    if (![self activeNode]) return;
    NodeCore::Field *field = [self activeNode]->getFields()[rowIndex];
    NSString *identifier = [aTableColumn identifier];
    if (!([identifier isEqualToString:@"value"] | [identifier isEqualToString:@"stepper"])) return; 
    if ([objectValue respondsToSelector:@selector(floatValue)]) {
        NSLog(@"Setting value to %@", objectValue);
        field->set([objectValue floatValue]);
        [[self windowController] activeNetworkModified]; 
    }
}

@end

