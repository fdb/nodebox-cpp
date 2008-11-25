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

#ifndef NodeLibrary_h
#define NodeLibrary_h

#include <QtCore/QDir>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "NodeLibraryVersion.h"
#include "NodeType.h"

namespace NodeCore {

class Node;

class NodeLibrary : public QObject
{
    Q_OBJECT
public:
    enum LibraryType {
        NativeType,
        PythonType
    };

    NodeLibrary(const QString& name, int version_major, int version_minor, int version_revision, const QDir& path);
    virtual ~NodeLibrary();

    // Attribute getters
    LibraryType libraryType();
    void setLibraryType(LibraryType libraryType);
    QString name() { return m_name; }
    QString label() { return m_label; }
    void setLabel(const QString& label);
    NodeLibraryVersion version() { return m_version; }
    QString versionAsString() { return m_version.toString(); }
    QDir path() { return m_path; }

    // Node type access
    int size() { return m_types.size(); }
    NodeType* nodeType(const QString& name) { return m_types[name]; }
    bool hasNodeType(const QString& name) { return m_types.contains(name); }
    QList<NodeType*> nodeTypes() { return m_types.values(); }

    // Library operations
    Node* createNode(const QString& name);

    // Loading is made public so you can catch errors at an opportune time,
    // not when loading is triggered at an arbitrary point.
    void load();
    void unload();
    void reload();
    bool isLoaded();

protected:
    void addNodeType(NodeType* nodeType);

private:
    // Disallow copy construction or assignment
    NodeLibrary(const NodeLibrary& other);
    NodeLibrary& operator=(const NodeLibrary& other);
    QString typesFile() const;

    QString m_name;
    QString m_label;
    NodeLibraryVersion m_version;
    LibraryType m_type;
    QMap<QString, NodeType*> m_types;
    QDir m_path;
    bool m_loaded;

    friend class TypesHandler;
};

} // namespace NodeCore

#endif // NodeLibrary_h
