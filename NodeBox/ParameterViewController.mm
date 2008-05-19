#import "ParameterViewController.h"

@implementation ParameterViewController

- (id)init
{
    if (![NSBundle loadNibNamed:@"ParameterView" owner:self]) {
        NSLog(@"Could not load nib ParameterView");
    }
    return self;
}

- (NSView *)view
{
    return _view;
}

- (void)activeNodeChanged
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
    } else {
        return @"invalid";
    }
}

- (void)tableView:(NSTableView *)aTableView setObjectValue:(id)objectValue forTableColumn:(NSTableColumn *)aTableColumn row:(NSInteger)rowIndex
{
    if (![self activeNode]) return;
    NodeCore::Field *field = [self activeNode]->getFields()[rowIndex];
    if (![[aTableColumn identifier] isEqualToString:@"value"]) return;
    if ([objectValue respondsToSelector:@selector(floatValue)]) {
        NSLog(@"Setting value to %@", objectValue);
        field->set([objectValue floatValue]);
    }
}

@end

