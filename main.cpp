#include <qapplication.h>

#include "nodeboxapplication.h"
#include "nodeboxdocument.h"

int main(int argc, char *argv[])
{
    NodeBoxApplication app(argc, argv);
    NodeBoxDocument doc;
    doc.show();
    return app.exec();
}
