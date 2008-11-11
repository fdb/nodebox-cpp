/*
 * This file is part of NodeBox.
 *
 * Copyright (C) 2008 Frederik De Bleser (frederik@pandora.be)
 *
 * NodeBox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NodeBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NodeBox.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include "NodeLibraryManager.h"

#include <stdio.h>
#include <string.h>

#include "posixutils.h"
#include "NodeLibrary.h"
#include "Node.h"

namespace NodeCore {

NodeLibraryManager::NodeLibraryManager()
                   : m_lookedForLibraries(false)
                   
{
}

NodeLibraryManager::~NodeLibraryManager()
{
    // Delete libraries.
}

/*! Converts a dirname like graphics-2.3.4 to a
    NodeLibrary("graphics", 2, 3, 4) object.
 */
NodeLibrary* NodeLibraryManager::libraryFromDirectory(const QDir& dir)
{
    // TODO: implement
    return NULL;
    /*
    char c_dirname[64];
    char name[32];
    strncpy(c_dirname, dirname.c_str(), 63);
    int major = 0, minor = 0, revision = 0;
    char* pch;
    if ((pch = strtok(c_dirname, "-")) != NULL)
        strncpy(name, pch, 31);
    if ((pch = strtok(NULL, ".")) != NULL)
        sscanf(pch, "%i", &major);
    if ((pch = strtok(NULL, ".")) != NULL)
        sscanf(pch, "%i", &minor);
    if ((pch = strtok(NULL, ".")) != NULL)
        sscanf(pch, "%i", &revision);

    // TODO: last argument shouldn't be here, but loaded from somewhere else, or dirname should be full.
    return new NodeLibrary(std::string(name), major, minor, revision, searchPath + '/' + dirname);
    */
    return NULL;
}

QList<NodeLibrary*> NodeLibraryManager::libraries()
{
    if (!m_lookedForLibraries)
        lookForLibraries();
    return m_libraries;
}

NodeLibrary* NodeLibraryManager::loadLatest(const QString& name)
{
    // TODO: We do not handle multiple versions yet.
    if (!m_lookedForLibraries)
        lookForLibraries();
    // TODO: Not entirely correct :)
    NodeLibrary* library = m_libraries[0];
    library->load();
    return library;
}

void NodeLibraryManager::appendSearchPath(const QDir& path)
{
    Q_ASSERT(!m_lookedForLibraries);
    m_searchPaths.append(path);
}

// Searches for available libraries in the plugin search path.
void NodeLibraryManager::lookForLibraries()
{
    Q_ASSERT(!m_lookedForLibraries);
    /*
    SearchPathList::iterator pathIter = m_searchPaths.begin();
    for (;pathIter!=m_searchPaths.end(); ++pathIter) {
        std::string searchPath = (*pathIter);
        posix_dirlist_t dirs = posix_listdir(searchPath.c_str(), POSIX_DIR);
        for (posix_diriter_t dirIter=dirs.begin(); dirIter!=dirs.end(); ++dirIter) {
            std::string dirname = (*dirIter);
            NodeLibrary* lib = dirname_to_library(searchPath, dirname);
            m_nodeLibraryMap.insert(std::pair<const NodeLibraryName, NodeLibrary*>(lib->getName(), lib));
        }
    }*/
    
    m_lookedForLibraries = true;
}

} // namespace NodeCore
