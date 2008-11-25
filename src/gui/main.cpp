#include "nodeboxapplication.h"

int main(int argc, char *argv[])
{
    NodeBoxApplication app(argc, argv);
    app.createNewDocument();
    return app.exec();
}
