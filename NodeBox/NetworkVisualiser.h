/*
 *  NetworkVisualiser.h
 *  NodeBox
 *
 *  Created by Frederik on 05/05/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
 
#ifndef NetworkVisualiser_h
#define NetworkVisualiser_h

#import <NodeCore/NodeCore.h>

class NetworkVisualiser : public NodeCore::CanvasNode
{
public:
    NetworkVisualiser();
protected:
    virtual void process();
};

#endif // NetworkVisualiser_h