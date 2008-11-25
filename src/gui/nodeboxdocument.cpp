#include "qvariant.h"

#include "network.h"
#include "node.h"
#include "nodeboxapplication.h"
#include "nodeboxdocument.h"
#include "nodelibrary.h"
#include "nodelibrarymanager.h"

using namespace NodeCore;

NodeBoxDocument::NodeBoxDocument(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    NodeBoxApplication *app = (NodeBoxApplication*)QApplication::instance(); //(NodeBoxApplication*)(qApp);//qobject_cast<NodeBoxApplication*>(qApp);
    NodeLibraryManager* manager = app->nodeLibraryManager();
    NodeLibrary* library = manager->loadLatest("core");

    Node *n = library->createNode("doublevalue");
    QVariantList values;
    values.append(QVariant(10.0));
    n->setValues("value", values);
    n->update();
    QVariantList outputValues = n->outputValues();
    Q_ASSERT(outputValues.size() == 1);
    Q_ASSERT(outputValues[0].toDouble() == 10.0);
}

NodeBoxDocument::~NodeBoxDocument()
{

}
