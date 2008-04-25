#ifndef NodeInfo_h
#define NodeInfo_h

#include <exception>

#include "Node.h"

namespace NodeCore {

class NodeLibrary;

typedef std::string NodeName;

typedef Node* (*NodeCreator)();

enum NodeLibraryType {
    kUnknown = 0,
    kNative,
    kPython,
    kUnsupported
};

typedef std::string NodeLibraryName;

class NodeCreationError : public std::exception
{
public:
    NodeCreationError(NodeLibraryName libraryName, NodeName nodeName, std::string msg="")
            : m_libraryName(libraryName), m_nodeName(nodeName), m_msg(msg) {}
    virtual ~NodeCreationError() throw() {}
    NodeLibraryName m_libraryName;
    NodeName m_nodeName;
    std::string m_msg;
};

class NodeInfo
{
public:
    NodeInfo(NodeLibrary& library, NodeName name, void* data);
    ~NodeInfo();
    
    NodeLibrary& getLibrary();
    NodeName getName();
    Node* create();

private:
    Node* createNativeNode();
    Node* createPythonNode();

    NodeLibrary& m_library;
    NodeName m_name;
    void* m_data;
};

} // namespace NodeCore

#endif // NodeInfo_h