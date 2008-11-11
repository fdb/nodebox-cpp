/********************************************************************************
** Form generated from reading ui file 'nodeboxdocument.ui'
**
** Created: Tue Nov 11 20:17:27 2008
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NODEBOXDOCUMENT_H
#define UI_NODEBOXDOCUMENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NodeBoxDocumentClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NodeBoxDocumentClass)
    {
    if (NodeBoxDocumentClass->objectName().isEmpty())
        NodeBoxDocumentClass->setObjectName(QString::fromUtf8("NodeBoxDocumentClass"));
    NodeBoxDocumentClass->setObjectName("NodeBoxDocumentClass");
    NodeBoxDocumentClass->resize(600, 400);
    menuBar = new QMenuBar(NodeBoxDocumentClass);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    NodeBoxDocumentClass->setMenuBar(menuBar);
    mainToolBar = new QToolBar(NodeBoxDocumentClass);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    NodeBoxDocumentClass->addToolBar(mainToolBar);
    centralWidget = new QWidget(NodeBoxDocumentClass);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    NodeBoxDocumentClass->setCentralWidget(centralWidget);
    statusBar = new QStatusBar(NodeBoxDocumentClass);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    NodeBoxDocumentClass->setStatusBar(statusBar);

    retranslateUi(NodeBoxDocumentClass);

    QMetaObject::connectSlotsByName(NodeBoxDocumentClass);
    } // setupUi

    void retranslateUi(QMainWindow *NodeBoxDocumentClass)
    {
    NodeBoxDocumentClass->setWindowTitle(QApplication::translate("NodeBoxDocumentClass", "NodeBoxDocument", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(NodeBoxDocumentClass);
    } // retranslateUi

};

namespace Ui {
    class NodeBoxDocumentClass: public Ui_NodeBoxDocumentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEBOXDOCUMENT_H
