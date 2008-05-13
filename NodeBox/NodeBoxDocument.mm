//
//  MyDocument.m
//  NodeBox
//
//  Created by Frederik on 30/04/08.
//  Copyright __MyCompanyName__ 2008 . All rights reserved.
//

#import "NodeBoxDocument.h"
#import "NodeBoxWindowController.h"

@implementation NodeBoxDocument

- (id)init
{
    self = [super init];
    if (self) {
        network = new NodeCore::Network();
        NodeCore::Node* n1 = new NodeCore::Node();
        n1->setName("node1");
        n1->setX(20);
        n1->setY(30);
        network->add(n1);
        NodeCore::Node* n2 = new NodeCore::Node();
        n2->setName("node2");
        n2->setX(220);
        n2->setY(30);
        network->add(n2);
        // Add your subclass-specific initialization here.
        // If an error occurs here, send a [self release] message and return nil.    
    }
    return self;
}

- (void)dealloc
{
    delete network;
    [super dealloc];
}

- (void)finalize
{
    delete network;
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
    NSLog(@"Making window controllers");
    NodeBoxWindowController *controller = [[[NodeBoxWindowController alloc] init] autorelease];
    [self addWindowController:controller];
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
    [super windowControllerDidLoadNib:aController];
    NSLog(@"setting network view");
    [networkView setDocument:self];
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

-(NodeCore::Network*) network
{
    return network;
}


-(NodeCore::Node*) createNode
{
    NodeCore::Node *node = new NodeCore::Node();
    node->setX(30);
    node->setY(50);
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Create Node"];
    }
    network->add(node);
    [networkView setNeedsDisplay:TRUE];
    return node;
}

-(void) addNode:(NodeCore::Node*) node
{
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Add Node"];
    }
    network->add(node);
}

-(BOOL) removeNode:(NodeCore::Node *)node
{
    if (node->getNetwork() != network) {
        return false;
    }
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] removeNode:node];
    if (![undo isUndoing]) {
        [undo setActionName:@"Remove Node"];
    }
    network->remove(node);
    // Not deleting the node, since the undoManager needs it.
    return true;
}

@end
