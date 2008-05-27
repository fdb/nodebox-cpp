//
//  NodeInfoWrapper.m
//  NodeBox
//
//  Created by Frederik on 27/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import "NodeInfoWrapper.h"


@implementation NodeInfoWrapper


- (id)initWithNodeInfo:(NodeCore::NodeInfo *)info
{
    self = [super init];
    name = [NSString stringWithCString:info->getName().c_str()];
    return self;
}

- (NSString *)name
{
    return name;
}

@end
