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
 
#import "NodeBoxDocument.h"
#import "NodeBoxWindowController.h"
#import "NodeBoxAppDelegate.h"

NSString *NodeType = @"NodeType";

@implementation NodeBoxDocument

- (id)init
{
    self = [super init];
    if (self) {
        NodeBoxAppDelegate *delegate = [[NSApplication sharedApplication] delegate];
        NodeCore::NodeLibraryManager *nlm = [delegate nodeLibraryManager];
        _rootNetwork = new NodeCore::Network();
        NodeCore::NodeLibrary *vectorLib = nlm->loadLatest("corevector");
        NodeCore::Node *rect1 = vectorLib->createNode("RectNode");
        NodeCore::Node *rect2 = vectorLib->createNode("RectNode");
        NodeCore::Node *oval1 = vectorLib->createNode("OvalNode");
        rect1->setX(100);
        rect1->setY(100);
        rect2->setX(200);
        rect2->setY(100);
        oval1->setX(300);
        oval1->setY(100);
        _rootNetwork->setUniqueNodeName(rect1);
        _rootNetwork->add(rect1);
        _rootNetwork->setUniqueNodeName(rect2);
        _rootNetwork->add(rect2);
        _rootNetwork->setUniqueNodeName(oval1);
        _rootNetwork->add(oval1);
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

@end
