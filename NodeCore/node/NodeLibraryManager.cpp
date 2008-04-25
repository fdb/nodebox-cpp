#include <iostream>

#include "NodeCore.h"

namespace NodeCore {

NodeLibraryManager::NodeLibraryManager()
{
    lookForLibraries();
}

NodeLibraryManager::~NodeLibraryManager()
{
    NodeLibraryMap::iterator iter = m_nodeLibraryMap.begin();
    for(;iter!=m_nodeLibraryMap.end(); ++iter) {
        delete (*iter).second;
    }
}

NodeLibrary* dirname_to_library(std::string dirname)
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
    return new NodeLibrary(std::string(name), major, minor, revision, NODE_LIBRARY_SEARCH_PATH + PATH_SEP + dirname);
}

NodeLibraryList NodeLibraryManager::libraries()
{
    NodeLibraryList libs;
    NodeLibraryMap::iterator iter = m_nodeLibraryMap.begin();
    for(;iter!=m_nodeLibraryMap.end(); ++iter) {
        NodeLibrary* pLib = (*iter).second;
        libs.push_back(pLib);
    }
    return libs;
}

NodeLibrary* NodeLibraryManager::loadLatest(NodeLibraryName name)
{
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

// Searches for available libraries in the plugin search path.
void NodeLibraryManager::lookForLibraries()
{
    m_nodeLibraryMap.clear();
    posix_dirlist_t dirs = posix_listdir(NODE_LIBRARY_SEARCH_PATH.c_str(), POSIX_DIR);
    for(posix_diriter_t iter=dirs.begin(); iter!=dirs.end(); ++iter) {
        std::string dirname = (*iter);
        NodeLibrary* lib = dirname_to_library(dirname);
        m_nodeLibraryMap.insert(std::pair<const NodeLibraryName, NodeLibrary*>(lib->getName(), lib));
    }
}

} // namespace NodeCore