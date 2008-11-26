#ifndef CoreVectorLibrary_h
#define CoreVectorLibrary_h

#include <qobject.h>
#include <qstring.h>
#include <qvector.h>
#include <nodetype.h>
#include <nodefactoryinterface.h>

using namespace NodeCore;

class CoreVectorFactory : public QObject, public NodeFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(NodeCore::NodeFactoryInterface)
    
public:
    Node *createNode(const NodeType *t) const;
};

# endif // CoreVectorLibrary_h
