//
//  MyDocument.m
//  NodeBox
//
//  Created by Frederik on 30/04/08.
//  Copyright __MyCompanyName__ 2008 . All rights reserved.
//

#import "NodeBoxDocument.h"
#import "NodeBoxWindowController.h"

NSString *NodeType = @"NodeType";

@implementation NodeBoxDocument

- (id)init
{
    self = [super init];
    if (self) {
        _rootNetwork = new NodeCore::Network();
        NodeCore::Node* n1 = new NodeCore::Node();
        _rootNetwork->setUniqueNodeName(n1);
        n1->setX(20);
        n1->setY(30);
        _rootNetwork->add(n1);
        NodeCore::Node* n2 = new NodeCore::Node();
        _rootNetwork->setUniqueNodeName(n2);
        n2->setX(220);
        n2->setY(30);
        _rootNetwork->add(n2);
        // Add your subclass-specific initialization here.
        // If an error occurs here, send a [self release] message and return nil.    
    }
    return self;
}

- (void)dealloc
{
    delete _rootNetwork;
    [super dealloc];
}

- (void)finalize
{
    delete _rootNetwork;
    [super finalize];
}

/*
- (NSString *)windowNibName
{
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"NodeBoxDocument";
}
*/

- (void)makeWindowControllers
{
    NodeBoxWindowController *controller = [[[NodeBoxWindowController alloc] init] autorelease];
    [self addWindowController:controller];
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
    [super windowControllerDidLoadNib:aController];
    // [networkView setDocument:self];
    // Add any code here that needs to be executed once the windowController has loaded the document's window.
}

- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError
{
    // Insert code here to write your document to data of the specified type. If the given outError != NULL, ensure that you set *outError when returning nil.

    // You can also choose to override -fileWrapperOfType:error:, -writeToURL:ofType:error:, or -writeToURL:ofType:forSaveOperation:originalContentsURL:error: instead.

    // For applications targeted for Panther or earlier systems, you should use the deprecated API -dataRepresentationOfType:. In this case you can also choose to override -fileWrapperRepresentationOfType: or -writeToFile:ofType: instead.

    if ( outError != NULL ) {
		*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
	}
	return nil;
}

- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError
{
    // Insert code here to read your document from the given data of the specified type.  If the given outError != NULL, ensure that you set *outError when returning NO.

    // You can also choose to override -readFromFileWrapper:ofType:error: or -readFromURL:ofType:error: instead. 
    
    // For applications targeted for Panther or earlier systems, you should use the deprecated API -loadDataRepresentation:ofType. In this case you can also choose to override -readFromFile:ofType: or -loadFileWrapperRepresentation:ofType: instead.
    
    if ( outError != NULL ) {
		*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
	}
    return YES;
}

-(NodeCore::Network*) rootNetwork
{
    return _rootNetwork;
}


-(NodeCore::Node*) createNode
{
    return [self createNodeAt:NSMakePoint(30, 30)];
}

-(NodeCore::Node*) createNodeAt:(NSPoint)point
{
    NSLog(@"Create node at %f, %f", point.x, point.y);
    NodeCore::Node *node = new NodeCore::Node();
    node->setX(point.x);
    node->setY(point.y);
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Create Node"];
    }
    _rootNetwork->add(node);
    _rootNetwork->setUniqueNodeName(node);
    // [networkView setNeedsDisplay:TRUE];
    return node;
}

-(void) addNode:(NodeCore::Node*) node
{
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Add Node"];
    }
    _rootNetwork->add(node);
    //[networkView setNeedsDisplay:TRUE];
}

-(BOOL) removeNode:(NodeCore::Node *)node
{
    if (node->getNetwork() != _rootNetwork) {
        return false;
    }
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Remove Node"];
    }
    _rootNetwork->remove(node);
    //[networkView setNeedsDisplay:TRUE];
    // Not deleting the node, since the undoManager needs it.
    return true;
}

@end
