//
//  NodeInfoWrapper.h
//  NodeBox
//
//  Created by Frederik on 27/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <NodeCore/NodeCore.h>

@interface NodeInfoWrapper : NSObject {
    NSString *name;
}

- (id)initWithNodeInfo:(NodeCore::NodeInfo *)info;
- (NSString *)name;
@end
