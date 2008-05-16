//
//  NetworkView.h
//  NodeBox
//
//  Created by Frederik on 05/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class NetworkViewController;
@class NodeBoxDocument;
class NetworkVisualiser;

@interface NetworkView : NSView {
    IBOutlet NetworkViewController *viewController;
    NodeBoxDocument* document;
    NetworkVisualiser* visualiser;
}

- (NetworkViewController*)controller;
- (void)setController:(NetworkViewController *)controller;
@end
