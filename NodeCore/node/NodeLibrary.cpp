#include "NodeCore.h"

namespace NodeCore {

NodeLibrary::NodeLibrary(NodeLibraryName name, int version_major, int version_minor, int version_revision, NodeLibraryPath path)
    : m_name(name), 
      m_version(NodeLibraryVersion(version_major, version_minor, version_revision)),
      m_path(path),
      m_type(kUnknown),
      m_loaded(false) { m_handle = NULL; }

NodeLibrary::~NodeLibrary() {
    unload();
}

NodeLibraryType NodeLibrary::getType() {
    return m_type;
}

// Can only be called by native libraries.
void NodeLibrary::addNodeInfo(NodeName name, NodeCreator creator) {
    assert (getLibraryType() == kNative);
    NodeInfo* info = new NodeInfo(*this, name, (void*)creator);
    m_nodes.push_back(info);
}

NodeInfo* NodeLibrary::getNodeInfo(NodeName name)
{
    if (!m_loaded) load();
    for (NodeInfoIterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter) {
        NodeInfo* info = (*iter);
        if (info->getName() == name) {
            return info;
        }
    }
    throw NodeInfoNotFound(name);
}

NodeInfoList NodeLibrary::getNodeInfoList()
{
    if (!m_loaded) load();
    return m_nodes;
}

NodeLibraryType NodeLibrary::getLibraryType()
{
    if (m_type != kUnknown) { return m_type; }

    // Node library detection type is based on naming conventions,
    // not configuration files.

    if (posix_file_exists(getNativeLibraryPath().c_str())) {
        m_type = kNative;
        return m_type;
    } 

    if (posix_file_exists(getPythonLibraryPath().c_str())) {
        m_type = kPython;
        return m_type;
    }

    m_type = kUnsupported;
    return m_type;
}

NodeLibraryVersion NodeLibrary::getVersion() { return m_version; }
std::string NodeLibrary::getVersionAsString() { return m_version.asString(); }

NodeLibraryName NodeLibrary::getName() { return m_name; }

Node* NodeLibrary::createNode(NodeName name) {
    try {
        NodeInfo* info = getNodeInfo(name);
        return info->create();
    } catch (NodeInfoNotFound) {
        throw NodeCreationError(m_name, name, "Unknown node name");
    }
}

// A native library has one file inside of the library folder,
// called <libname>.nbl (NodeBox Library)
// The full path would be plugins/libname-1.2.3/libname.nbl
std::string NodeLibrary::getNativeLibraryPath() {
    return m_path + PATH_SEP + m_name + ".nbl";
}

// A python library has, amongst others, a file inside of the library folder
// called <libname>.py
// The full path would be plugins/libname-1.2.3/libname.py
std::string NodeLibrary::getPythonLibraryPath() {
    return m_path + PATH_SEP + m_name + ".py";
}

std::string NodeLibrary::getLibraryPath() {
    NodeLibraryType type = getLibraryType();
    switch(type) {
        case kNative:
            return getNativeLibraryPath();
            break;
        case kPython:
            return getPythonLibraryPath();
            break;
        default:
            throw NodeLibraryLoadError(m_name, "Unsupported library type");
    }
}

void NodeLibrary::load()
{
    if (m_loaded) {
        // std::cout << "[NL] Library " << m_name << " already loaded." << std::endl;
        return;
    }
    
    // TODO: what to do if there is no path?
    // std::cout << "[NL] Loading library " << m_path << std::endl;
    
    NodeLibraryType type = getLibraryType();
    switch(type) {
        case kNative:
            loadNativeLibrary();
            break;
        case kPython:
            loadPythonLibrary();
            break;
        default:
            throw NodeLibraryLoadError(m_name, "Unsupported library type");
    }
    assert(m_loaded);
}

bool NodeLibrary::isLoaded() {
    return m_loaded;
}

void NodeLibrary::unload()
{
    if (!m_loaded) {
        return;
    }
    
    // std::cout << "[NL] Unloading library " << getLibraryPath() << std::endl;

    NodeLibraryType type = getLibraryType();
    switch(type) {
        case kNative:
            unloadNativeLibrary();
            break;
        case kPython:
            unloadPythonLibrary();
            break;
        default:
            throw NodeLibraryLoadError(m_name, "Unsupported library type");
    }
    assert(!m_loaded);
    for (NodeInfoIterator iter = m_nodes.begin(); iter != m_nodes.end(); ++iter) {
        delete (*iter);
    }
}

void NodeLibrary::loadNativeLibrary()
{
    char *dlsym_error;
    if (m_handle) {
        // std::cout << "[NL] Library " << m_name << " already loaded." << std::endl;
        assert(m_loaded);
        return;
    }
    
    // Open the library
    void* lib = dlopen(getNativeLibraryPath().c_str(), RTLD_LAZY);
    if (!lib) {
        std::cerr << "Cannot open library " << getNativeLibraryPath() << ": " << dlerror() << std::endl;
        throw NodeLibraryLoadError(m_name, "open error");
    }
    
    // If the library was loaded, set the handle
    m_handle = lib;

    // Load the info symbol
    nodeLibraryInfoFunction infoFunction = (nodeLibraryInfoFunction)dlsym(lib, "nodeLibraryInfo");
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "#ERR Not a valid library: cannot load the nodeLibraryInfo symbol: " << dlsym_error << getNativeLibraryPath() << std::endl;
        // TODO: teardown
        throw NodeLibraryLoadError(m_name, "symbol error");
    }
    
    // Get the node information
    infoFunction(*this);
    
    m_loaded = true;
}

void NodeLibrary::loadPythonLibrary()
{
    std::string initCode = "import sys\nsys.path.append('" + m_path + "')\n";
    Py_Initialize();
    PyRun_SimpleString(initCode.c_str());
    PyObject* py_module = PyImport_ImportModule(m_name.c_str());
    if (!py_module) {
        std::cerr << "Cannot open library " << getPythonLibraryPath() << std::endl;
        throw NodeLibraryLoadError(m_name, "open error");
    }
    m_handle = py_module;
    // Find all nodes.

    PyObject* module_dict = PyModule_GetDict(py_module); /* borrowed */
    PyObject* module_dict_items = PyDict_Items(module_dict);
    int size = PyList_Size(module_dict_items);
    for (int i=0; i < size; i++) {
        PyObject* module_item_tuple = PyList_GetItem(module_dict_items, i); /* borrowed */
        if (!PyTuple_Check(module_item_tuple) || PyTuple_Size(module_item_tuple) != 2) {
            std::cerr << "No tuples in library dict " << getPythonLibraryPath() << std::endl;
            throw NodeLibraryLoadError(m_name, "module dict error");
        }
        PyObject* module_item_name = PyTuple_GetItem(module_item_tuple, 0); /* borrowed */
        PyObject* module_item_value = PyTuple_GetItem(module_item_tuple, 1); /* borrowed */
        if (!PyType_Check(module_item_value)) {
            // std::cout << "[NL] Skipping " << PyString_AsString(module_item_name) << std::endl;
            continue;
        }
        PyObject* node_method_process = PyObject_GetAttrString(module_item_value, "process");
        if (!node_method_process) {
            // std::cout << "[NL] Skipping " << PyString_AsString(module_item_name) <<": no method process" << std::endl;
            continue;
        }
        if (!PyMethod_Check(node_method_process)) {
            // std::cout << "[NL] Skipping " << PyString_AsString(module_item_name) <<": process is not a method" << std::endl;
            Py_DECREF(node_method_process);
            continue;
        }
        // std::cout << "[NL] Looks okay: " << PyString_AsString(module_item_name) << std::endl;
        Py_DECREF(node_method_process);
        NodeInfo* info = new NodeInfo(*this, NodeName(PyString_AsString(module_item_name)), module_item_value);
        m_nodes.push_back(info);
    }
    Py_DECREF(module_dict_items);
    m_loaded = true;
}

void NodeLibrary::unloadNativeLibrary()
{
    if (m_handle) {
        dlclose(m_handle);
    }
    m_loaded = false;
}

void NodeLibrary::unloadPythonLibrary()
{
    if (m_handle) {
        Py_DECREF((PyObject*)m_handle);
    }
    m_loaded = false;
}

} // namespace NodeCore