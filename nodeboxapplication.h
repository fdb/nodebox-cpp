#ifndef NODEBOXAPPLICATION_H
#define NODEBOXAPPLICATION_H

#include <qapplication.h>
#include <qdir.h>
#include <qobject.h>
#include <qsettings.h>

#include "nodelibrarymanager.h"

using namespace NodeCore;

class NodeBoxApplication : public QApplication
{
    Q_OBJECT
public:
    NodeBoxApplication( int & argc, char ** argv );
    virtual ~NodeBoxApplication();

    void createNewDocument();
    void exit();

    QDir lastDirectory();
    void setLastDirectory(const QDir &lastDirectory);

    QDir userLibraryDirectory();

    NodeLibraryManager *nodeLibraryManager() const;

private:
    void ensureLibraryDirectory();

    NodeLibraryManager *m_manager;
    QSettings m_settings;
    QDir m_lastDirectory;
};

#endif // NODEBOXAPPLICATION_H
