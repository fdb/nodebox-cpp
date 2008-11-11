#include <qdesktopservices.h>

#include "nodeboxapplication.h"

using namespace NodeCore;

NodeBoxApplication::NodeBoxApplication( int & argc, char ** argv )
    : QApplication(argc, argv)
{
    setQuitOnLastWindowClosed(false);
    setOrganizationName("NodeBox");
    setOrganizationDomain("nodebox.net");
    setApplicationName("NodeBox");
    QString homeDirectory = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
    QString lastDirectory = m_settings.value("lastDirectory", QVariant(homeDirectory)).toString();
    m_lastDirectory = QDir(lastDirectory);
    ensureLibraryDirectory();
    QList<QDir> libraryDirectories;
    libraryDirectories.append(userLibraryDirectory());
    m_manager = new NodeLibraryManager();
    m_manager->appendSearchPath(userLibraryDirectory());
}

NodeBoxApplication::~NodeBoxApplication()
{
    delete m_manager;
}

void NodeBoxApplication::createNewDocument()
{
}

void NodeBoxApplication::exit()
{
}

QDir NodeBoxApplication::lastDirectory()
{
    return m_lastDirectory;
}

void NodeBoxApplication::setLastDirectory(const QDir &lastDirectory)
{
    m_lastDirectory = lastDirectory;
    m_settings.setValue("lastDirectory", QVariant(m_lastDirectory.absolutePath()));
}

void NodeBoxApplication::ensureLibraryDirectory()
{
}

QDir NodeBoxApplication::userLibraryDirectory()
{
    QString libraryDirectory = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
    libraryDirectory += "/Library/Application Support/NodeBox2";
    return QDir(libraryDirectory);
}

NodeLibraryManager *NodeBoxApplication::nodeLibraryManager() const
{
    return m_manager;
}


