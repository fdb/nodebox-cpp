//
//  NetworkView.h
//  NodeBox
//
//  Created by Frederik on 05/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NodeBoxDocument;
class NetworkVisualiser;

@interface NetworkView : NSView {
    NodeBoxDocument* document;
    NetworkVisualiser* visualiser;
}

- (NodeBoxDocument*)document;
- (void)setDocument:(NodeBoxDocument*)document;
@end
