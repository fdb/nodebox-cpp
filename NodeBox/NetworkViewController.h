#import <NodeCore/NodeCore.h>
#import <Cocoa/Cocoa.h>
#import "ViewController.h"

@interface NodeWrapper : NSObject {
    NodeCore::Node *_theNode;
}
- (id)initWithNode:(NodeCore::Node *)node;
- (NodeCore::Node*)node;
@end

@interface FieldWrapper : NSObject {
    NodeCore::Field *_field;
}
- (id)initWithField:(NodeCore::Field *)field;
- (NodeCore::Field*)field;
@end

@interface NetworkViewController : ViewController {
    IBOutlet NSView *_view;
    IBOutlet NSMenu *nodeContextMenu;
    NodeCore::Node *_contextNode;
}

- (NSView *)view;
- (void)contextMenuForNode:(NodeCore::Node *)node event:(NSEvent *)theEvent;
- (void)deleteNode:(id)sender;
- (void)renameNode:(id)sender;

@end
