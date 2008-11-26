#include "qdebug.h"

#include "PythonQt.h"

#include "network.h"
#include "node.h"
#include "nodeboxapplication.h"
#include "nodeboxdocument.h"
#include "nodelibrary.h"
#include "nodelibrarymanager.h"

using namespace NodeCore;

NodeBoxDocument::NodeBoxDocument(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags),
      m_context(new GraphicsContext()),
      m_viewer(new CanvasViewer()),
      m_editor(new CodeEditor()),
      m_logger(new Logger()),
      m_editorLoggerSplit(new QSplitter(Qt::Vertical)),
      m_viewerCodeSplit(new QSplitter(Qt::Horizontal))
{
    /*
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
    */

    createMenu();

    m_editorLoggerSplit->addWidget(m_editor);
    m_editorLoggerSplit->addWidget(m_logger);
    m_viewerCodeSplit->addWidget(m_viewer);
    m_viewerCodeSplit->addWidget(m_editorLoggerSplit);
    setCentralWidget(m_viewerCodeSplit);
    resize(800, 600);

    PythonQt::init();
    connect(PythonQt::self(), SIGNAL(pythonStdOut(const QString&)), m_logger, SLOT(addInfo(const QString&)));
    connect(PythonQt::self(), SIGNAL(pythonStdErr(const QString&)), m_logger, SLOT(addError(const QString&)));
}

NodeBoxDocument::~NodeBoxDocument()
{
    delete m_context;
    delete m_viewer;
    delete m_editor;
    delete m_logger;
    delete m_editorLoggerSplit;
    delete m_viewerCodeSplit;
}

void NodeBoxDocument::createMenu()
{
    m_menuBar = new QMenuBar();
    QMenu *pythonMenu = m_menuBar->addMenu("Python");
    QAction *runAction = pythonMenu->addAction("Run");
    runAction->setShortcut(tr("Ctrl+R"));
    runAction->connect(runAction, SIGNAL(triggered()), this, SLOT(runPython()));
    setMenuBar(m_menuBar);
}

void NodeBoxDocument::runPython()
{
    // TODO: reset context.
    m_context->canvas()->clear();
    m_logger->clear();
    PythonQtObjectPtr mainModule = PythonQt::self()->getMainModule();
    mainModule.addObject("ctx", m_context);
    QVariant result = mainModule.evalScript(m_editor->toPlainText(), Py_file_input);
    qDebug() << "runPython" << m_editor->toPlainText() << ":" << result;
    m_logger->addInfo(result.toString());
    m_viewer->setCanvas(m_context->canvas());
}
