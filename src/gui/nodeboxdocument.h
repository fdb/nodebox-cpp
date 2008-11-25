#ifndef NODEBOXDOCUMENT_H
#define NODEBOXDOCUMENT_H

#include <QtGui/QMainWindow>

class NodeBoxDocument : public QMainWindow
{
    Q_OBJECT

public:
    NodeBoxDocument(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~NodeBoxDocument();

};

#endif // NODEBOXDOCUMENT_H
