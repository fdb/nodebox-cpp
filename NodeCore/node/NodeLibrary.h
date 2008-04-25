#ifndef NodeLibrary_h
#define NodeLibrary_h

#include <dlfcn.h>
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <Python/Python.h>

#include "Node.h"
#include "NodeInfo.h"
#include "PythonNode.h"
#include "posixutils.h"

namespace NodeCore {

const std::string LIBRARY_NATIVE = "native";
const std::string LIBRARY_PYTHON = "python";

// See http://en.wikipedia.org/wiki/Software_versioning
// GNU version numbering scheme
class NodeLibraryVersion
{
public:
    NodeLibraryVersion(int version_major, int version_minor, int version_revision)
        : m_version_major(version_major), 
          m_version_minor(version_minor),
          m_version_revision(version_revision) {}
          
    NodeLibraryVersion() { }
    
    NodeLibraryVersion& operator=(const NodeLibraryVersion& other)
    {
        if (this== &other) return *this;
        //std::cout << "NodeLibraryVersion: operator= " << other.asString() << std::endl;
        m_version_major = other.m_version_major;
        m_version_minor = other.m_version_minor;
        m_version_revision = other.m_version_revision;
        return *this;
    }

    int getMajor() { return m_version_major; }
    int getMinor() { return m_version_minor; }
    int getRevision() { return m_version_revision; }

    std::string asString() {
        std::stringstream version(""); // TODO: remove ""?
        version << m_version_major << "." << m_version_minor << "." << m_version_revision;
        return version.str();
    }
      
private:
    int m_version_major;
    int m_version_minor;
    int m_version_revision;
};

const std::string PATH_SEP = "/";

typedef std::vector<NodeInfo*> NodeInfoList;
typedef NodeInfoList::iterator NodeInfoIterator;
typedef std::string NodeLibraryPath;

class NodeLibraryLoadError : public std::exception
{
public:
    NodeLibraryLoadError(NodeLibraryName name, std::string msg="")
            : m_name(name), m_msg(msg) {}
    virtual ~NodeLibraryLoadError() throw() {}
    std::string getMessage() { return m_msg; }
    NodeLibraryName m_name;
    std::string m_msg;
};


class NodeProcessingError : public std::exception
{
public:
    NodeProcessingError(const Node& node, std::string msg="")
            : m_node(node), m_msg(msg) {}
    virtual ~NodeProcessingError() throw() {}
    const Node& m_node;
    std::string m_msg;
};

class NodeInfoNotFound : public std::exception
{
public:
    NodeInfoNotFound(NodeName name)
            : m_name(name) {}
    virtual ~NodeInfoNotFound() throw() {}
    NodeName getName() { return m_name; }
    NodeName m_name;
};

class NodeLibrary;
typedef void (*nodeLibraryInfoFunction)(NodeLibrary&);

// NodeLibrary can load both native and Python libraries.
// They are not split out because we only support those two types
// at the moment, so the additional overhead is not worth it.

// A Node Library is a collection of nodes.
// Each libary has an identifier and a version number.
// A Node's fully qualified name (FQN) contains the node identifier
// and version number, like this: net.nodebox.graphics.Wiggle[1.0.2]
class NodeLibrary
{
public:
    NodeLibrary(NodeLibraryName name, int version_major, int version_minor, int version_revision, NodeLibraryPath path);    
    virtual ~NodeLibrary();

    NodeLibraryType getType();

    // Can only be called by native libraries.
    void addNodeInfo(NodeName name, NodeCreator creator);
    NodeInfo* getNodeInfo(NodeName name);
    NodeInfoList getNodeInfoList();
    
    NodeLibraryType getLibraryType();

    NodeLibraryVersion getVersion();
    std::string getVersionAsString();
    
    NodeLibraryName getName();
    
    Node* createNode(NodeName name);

    // Loading is made public so you can catch errors at an opportune time,
    // not when loading is triggered at an arbitrary point.
    void load();
    bool isLoaded();
    
private:
    // A native library has one file inside of the library folder,
    // called <libname>.nbl (NodeBox Library)
    // The full path would be plugins/libname-1.2.3/libname.nbl
    std::string getNativeLibraryPath();
    // A python library has, amongst others, a file inside of the library folder
    // called <libname>.py
    // The full path would be plugins/libname-1.2.3/libname.py
    std::string getPythonLibraryPath();
    std::string getLibraryPath();
    void unload();
    void loadNativeLibrary();
    void loadPythonLibrary();
    void unloadNativeLibrary();
    void unloadPythonLibrary();
    Node* createNativeNode(NodeName name);
    Node* createPythonNode(NodeName name);

    NodeLibraryName m_name;
    NodeInfoList m_nodes;
    NodeLibraryVersion m_version;
    NodeLibraryPath m_path;
    NodeLibraryType m_type;
    bool m_loaded;
    void* m_handle;
};

} // namespace NodeCore

#endif // NodeLibrary_h
