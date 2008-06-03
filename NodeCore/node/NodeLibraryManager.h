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

#ifndef NodeLibraryManager_h
#define NodeLibraryManager_h

#include "NodeLibrary.h"
#include "Node.h"

#include <string>
#include <exception>
#include <vector>
#include <map>

namespace NodeCore {

typedef std::vector<NodeLibraryName> NodeLibraryNameList;
typedef NodeLibraryNameList::iterator NodeLibraryNameIterator;

// Converts a dirname like graphics-2.3.4 to a 
// NodeLibrary("graphics", 2, 3, 4) object.
NodeLibrary* dirname_to_library(std::string searchPath, std::string dirname);

typedef std::multimap<NodeLibraryName,NodeLibrary*> NodeLibraryMap;
typedef std::vector<NodeLibrary*> NodeLibraryList;
typedef NodeLibraryList::iterator NodeLibraryIterator;

class NodeLibraryNotFound : public std::exception
{
public:
    NodeLibraryNotFound(NodeLibraryName name)
            : m_name(name) {}
    virtual ~NodeLibraryNotFound() throw() {}
    NodeLibraryName getName() { return m_name; }
    NodeLibraryName m_name;
};

class NodeLibraryManager
{
public:
    
    NodeLibraryManager(std::string searchPath=".");
    ~NodeLibraryManager();
    
    // Shows unique names of libraries
    // std::vector<NodeLibraryName> libraryNames()
    // Returns a list of all NodeLibrary objects (all versions)
    // NodeLibraryList libraries()
    // Returns only the latest versions of all NodeLibrary objects
    // NodeLibraryList latestLibraries()
    // Loads the latest version of the specified library
    // NodeLibrary loadLatest(NodeLibraryName name)
    // Returns all versions of this library
    // std::vector<NodeLibraryVersion> versions(NodeLibraryName name)
    // Returns the latest version of this library
    // NodeLibraryVersion latestVersion(NodeLibraryName name)
    
    // Available versions of a library
    // NodeLibraryList libraryVersions(NodeLibraryName name)
    
    // Retrieve the latest versions 
    
    /* deprecated
    std::string findLibrary(NodeLibraryName name)
    {
        return PLUGIN_SEARCH_PATH + PATH_SEP + name + PATH_SEP + name + ".nbl";
    }
    */
    
    NodeLibraryList libraries();
    NodeLibrary* loadLatest(NodeLibraryName name);

    void appendSearchPath(std::string path);    

private:
    // Searches for available libraries in the plugin search path.
    void lookForLibraries();
    
    typedef std::vector<std::string> SearchPathList;

    SearchPathList m_searchPaths;
    NodeLibraryMap m_nodeLibraryMap;
    bool m_lookedForLibraries;
};

} // namespace NodeCore

#endif // NodeLibraryManager_h