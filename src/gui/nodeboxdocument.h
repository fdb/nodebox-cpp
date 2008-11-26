#ifndef NODEBOXDOCUMENT_H
#define NODEBOXDOCUMENT_H

#include "qmainwindow.h"
#include "qsplitter.h"
#include "qmenubar.h"

#include "canvasviewer.h"
#include "codeeditor.h"
#include "graphicscontext.h"
#include "logger.h"

class NodeBoxDocument : public QMainWindow
{
    Q_OBJECT

public:
    NodeBoxDocument(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~NodeBoxDocument();

private slots:
    void runPython();

private:
    void createMenu();

    GraphicsContext *m_context;
    CanvasViewer *m_viewer;
    CodeEditor *m_editor;
    Logger *m_logger;
    QSplitter *m_editorLoggerSplit;
    QSplitter *m_viewerCodeSplit;
    QMenuBar *m_menuBar;
};

#endif // NODEBOXDOCUMENT_H
