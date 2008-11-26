#ifndef RectNode_h
#define RectNode_h

#include <qobject.h>
#include <node.h>

using namespace NodeCore;

namespace CoreVector {

class RectNode : public Node
{
    Q_OBJECT
public:
    virtual bool process();
};

} // namespace CoreVector

#endif // RectNode_h
