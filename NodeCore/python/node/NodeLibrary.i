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
          
    NodeLibraryVersion()
        : m_version_major(0),
          m_version_minor(0),
          m_version_revision(0) {}
          
    int getMajor() { return m_version_major; }
    int getMinor() { return m_version_minor; }
    int getRevision() { return m_version_revision; }

    std::string asString();
};

const std::string PATH_SEP = "/";

typedef std::vector<NodeInfo*> NodeInfoList;
typedef NodeInfoList::iterator NodeInfoIterator;
typedef std::string NodeLibraryPath;

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
    
};

} // namespace NodeCore
