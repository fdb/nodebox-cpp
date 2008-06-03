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

NodeLibraryManager::NodeLibraryManager(std::string searchPath)
                   : m_searchPaths(SearchPathList()),
                     m_nodeLibraryMap(NodeLibraryMap()),
                     m_lookedForLibraries(false)
                   
{
    m_searchPaths.push_back(searchPath);
}

NodeLibraryManager::~NodeLibraryManager()
{
    NodeLibraryMap::iterator iter = m_nodeLibraryMap.begin();
    for (;iter!=m_nodeLibraryMap.end(); ++iter) {
        delete (*iter).second;
    }
}

NodeLibrary* dirname_to_library(std::string searchPath, std::string dirname)
{
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
    return new NodeLibrary(std::string(name), major, minor, revision, searchPath + PATH_SEP + dirname);
}

NodeLibraryList NodeLibraryManager::libraries()
{
    if (!m_lookedForLibraries)
        lookForLibraries();
    NodeLibraryList libs;
    NodeLibraryMap::iterator iter = m_nodeLibraryMap.begin();
    for (;iter!=m_nodeLibraryMap.end(); ++iter) {
        NodeLibrary* pLib = (*iter).second;
        libs.push_back(pLib);
    }
    return libs;
}

NodeLibrary* NodeLibraryManager::loadLatest(NodeLibraryName name)
{
    if (!m_lookedForLibraries)
        lookForLibraries();
    if (m_nodeLibraryMap.count(name) == 0) {
        throw NodeLibraryNotFound(name);
    }
    // TODO: Handle multiple versions
    assert(m_nodeLibraryMap.count(name) == 1);
    NodeLibraryMap::iterator iter = m_nodeLibraryMap.find(name);
    NodeLibrary* lib = (*iter).second;
    lib->load();
    return lib;
}

void NodeLibraryManager::appendSearchPath(std::string path)
{
    assert(!m_lookedForLibraries);
}

// Searches for available libraries in the plugin search path.
void NodeLibraryManager::lookForLibraries()
{
    assert(!m_lookedForLibraries);
    
    SearchPathList::iterator pathIter = m_searchPaths.begin();
    for (;pathIter!=m_searchPaths.end(); ++pathIter) {
        std::string searchPath = (*pathIter);
        posix_dirlist_t dirs = posix_listdir(searchPath.c_str(), POSIX_DIR);
        for (posix_diriter_t dirIter=dirs.begin(); dirIter!=dirs.end(); ++dirIter) {
            std::string dirname = (*dirIter);
            NodeLibrary* lib = dirname_to_library(searchPath, dirname);
            m_nodeLibraryMap.insert(std::pair<const NodeLibraryName, NodeLibrary*>(lib->getName(), lib));
        }
    }
    
    m_lookedForLibraries = true;
}

} // namespace NodeCore