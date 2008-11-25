#ifndef NODEBOXDOCUMENT_H
#define NODEBOXDOCUMENT_H

#include <QtGui/QMainWindow>
#include "ui_nodeboxdocument.h"

class NodeBoxDocument : public QMainWindow
{
    Q_OBJECT

public:
    NodeBoxDocument(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~NodeBoxDocument();

private:
    Ui::NodeBoxDocumentClass ui;
};

#endif // NODEBOXDOCUMENT_H
