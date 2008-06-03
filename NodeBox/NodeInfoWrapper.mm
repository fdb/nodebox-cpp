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
 
#import "NodeInfoWrapper.h"
#import "NodeBoxAppDelegate.h"

@implementation NodeInfoWrapper

+ (NodeInfoWrapper *)wrapperWithIdentifier:(NSString *)identifier
{
    NSArray *idArray = [identifier componentsSeparatedByString:@":"];
    if ([idArray count] != 2) {
        NSLog(@"NodeInfoWrapper: Invalid identifier '%@'", identifier);
        return NULL;
    }
    NSString *libName = [idArray objectAtIndex:0];
    NSString *nodeName = [idArray objectAtIndex:1];

    NodeBoxAppDelegate *appDelegate = [[NSApplication sharedApplication] delegate];    
    NodeCore::NodeLibraryManager *manager = [appDelegate nodeLibraryManager];
    NodeCore::NodeLibrary *lib = manager->loadLatest([libName UTF8String]);
    // TODO: Memory leak -- who will delete this info obj?
    NodeCore::NodeInfo *info = lib->getNodeInfo([nodeName UTF8String]);
    return [[NodeInfoWrapper alloc] initWithNodeInfo:info];
}

- (id)initWithNodeInfo:(NodeCore::NodeInfo *)aInfo
{
    self = [super init];
    info = aInfo;
    return self;
}

- (NodeCore::NodeInfo *)nodeInfo
{
    return info;
}

- (NSString *)libraryName
{
    return [NSString stringWithCString:info->getLibrary().getName().c_str()];
}

- (NSString *)nodeName
{
    return [NSString stringWithCString:info->getName().c_str()];
}

- (NSString *)identifier
{
    return [NSString stringWithFormat:@"%@:%@", [self libraryName], [self nodeName]];
}

@end
