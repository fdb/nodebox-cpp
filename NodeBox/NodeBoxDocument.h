//
//  MyDocument.h
//  NodeBox
//
//  Created by Frederik on 30/04/08.
//  Copyright __MyCompanyName__ 2008 . All rights reserved.
//


#import <Cocoa/Cocoa.h>
#import <NodeCore/NodeCore.h>

@class NetworkView;

@interface NodeBoxDocument : NSDocument
{
@public
    NodeCore::Network* network;
    NetworkView* networkView;
}

-(NodeCore::Network*) network;
@end
