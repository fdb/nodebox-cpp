#import <NodeCore/NodeCore.h>
#import "NetworkViewController.h"
#import "NetworkView.h"
#import "NodeBoxWindowController.h"

@implementation NodeWrapper

- (id)initWithNode:(NodeCore::Node *)node
{
    self = [super init];
    _theNode = node;
    return self;
}

- (NodeCore::Node*)node
{
    return _theNode;
}

@end

@implementation FieldWrapper

- (id)initWithField:(NodeCore::Field *)field
{
    self = [super init];
    _field = field;
    return self;
}

- (NodeCore::Field*)field
{
    return _field;
}

@end

@implementation NetworkViewController

- (id)init
{
    self = [super init];
    if (![NSBundle loadNibNamed:@"NetworkView" owner:self]) {
        NSLog(@"Could not load nib NetworkView");
    }
    [(NetworkView *)_view setController:self];
    return self;
}

- (NSView *)view
{
    return _view;
}

- (void)contextMenuForNode:(NodeCore::Node *)node event:(NSEvent *)theEvent
{
    _contextNode = node;
    [NSMenu popUpContextMenu:nodeContextMenu withEvent:theEvent forView:[self view]];   
}

- (void)deleteNode:(id)sender
{
    if (!_contextNode) return;
    [[self windowController] removeNode:_contextNode];
}

- (void)renameNode:(id)sender
{
    // TODO: implement
}

@end
