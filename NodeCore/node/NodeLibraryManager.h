#ifndef NodeLibraryManager_h
#define NodeLibraryManager_h

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <stdio.h>
#include <string.h>

#include "posixutils.h"
#include "NodeLibrary.h"
#include "Node.h"

namespace NodeCore {

const std::string NODE_LIBRARY_SEARCH_PATH = "plugins";

typedef std::vector<NodeLibraryName> NodeLibraryNameList;
typedef NodeLibraryNameList::iterator NodeLibraryNameIterator;

// Converts a dirname like graphics-2.3.4 to a 
// NodeLibrary("graphics", 2, 3, 4) object.
NodeLibrary* dirname_to_library(std::string dirname);

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
    
    NodeLibraryManager();
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
private:
    // Searches for available libraries in the plugin search path.
    void lookForLibraries();

    NodeLibraryMap m_nodeLibraryMap;
};

} // namespace NodeCore

#endif // NodeLibraryManager_h