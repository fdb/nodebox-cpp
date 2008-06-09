%module(directors="1") nodecore
#pragma SWIG nowarn=512

// This code makes sure std::exceptions are wrapped in SWIG runtime exceptions,
// instead of crashing the application.
%include "exception.i"
%exception {
  try {
    $action
  } catch (const std::exception& e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  }
}

%include "std_string.i"


%{
#include <NodeCore/NodeCore.h>
%}

%include "node/Connection.i"
%include "node/Parameter.i"
%include "node/Node.i"
%include "node/Network.i"
%include "node/NodeInfo.i"
%include "node/NodeLibrary.i"
%include "node/NodeLibraryManager.i"

%include "graphics/Utils.i"
%include "graphics/Rect.i"
%include "graphics/Color.i"
%include "graphics/Transform.i"
%include "graphics/PathElement.i"
%include "graphics/Point.i"
%include "graphics/Grob.i"
%include "graphics/BezierPath.i"
%include "graphics/Canvas.i"