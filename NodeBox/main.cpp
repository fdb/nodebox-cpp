#include <QtGui/QApplication>

//#include <NodeCore/Node>
//#include <NodeCore/Network>

#include "../NodeCore/node/Node.h"
#include "../NodeCore/node/Network.h"

#include "NodeBoxDocument.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NodeBoxDocument w;
    w.show();


    return a.exec();
}
