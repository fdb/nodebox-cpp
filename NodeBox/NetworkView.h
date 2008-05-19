//
//  NetworkView.h
//  NodeBox
//
//  Created by Frederik on 05/05/08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <NodeCore/NodeCore.h>

@class NetworkViewController;
class NetworkVisualiser;

enum DragModeType {
    kNotDragging,
};

@interface NetworkView : NSView {
    IBOutlet NetworkViewController *viewController;
    NetworkVisualiser* visualiser;
    NodeCore::Node *_draggingNode;
    NodeCore::Node *_dragOverNode;
    NSPoint _dragPoint;
    bool _startedDragging;
    NodeCore::Node *_deferredDraggingNode;
    NSPoint _clickPoint;
}

- (NetworkViewController*)controller;
- (void)setController:(NetworkViewController *)controller;

- (NodeCore::Node *)findNodeAt:(NSPoint) point;
- (void)_drawNode:(NodeCore::Node *)node;
- (void)_drawConnectionWithInputField:(NodeCore::Field *)input outputField:(NodeCore::Field *)output;
- (void)_drawConnectionLineFrom:(NSPoint)p1 to:(NSPoint)p2;
@end
