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

#include "Node.h"
#include "NodeLibrary.h"
#include "NodeLibraryVersion.h"
#include "TypesHandler.h"

#include <QtCore/QFile>
#include <QtXml/QXmlSimpleReader>
#include <QtXml/QXmlInputSource>

namespace NodeCore {

/*! Constructs a new NodeLibrary.The path is the path of the directory containing the types.xml file.
*/
NodeLibrary::NodeLibrary(const QString& name, int version_major, int version_minor, int version_revision, const QDir& path)
    : m_name(name),
      m_version(NodeLibraryVersion(version_major, version_minor, version_revision)),
      m_path(path),
      m_loaded(false)
{
}

NodeLibrary::~NodeLibrary()
{
    unload();
}

NodeLibrary::LibraryType NodeLibrary::libraryType()
{
    load();
    return m_type;
}

void NodeLibrary::setLibraryType(NodeLibrary::LibraryType libraryType)
{
    m_type = libraryType;
}

void NodeLibrary::setLabel(const QString& label) {
    m_label = label;
}

// Library loading/unloading

QString NodeLibrary::typesFile() const
{
    // TODO: Correct path joining
    QString typesFileName(m_path.absolutePath());
    typesFileName.append('/');
    typesFileName.append("types.xml");
    return typesFileName;
}

void NodeLibrary::load()
{
    if (m_loaded) return;
     QFile *file = new QFile(typesFile());
     QXmlSimpleReader xmlReader;
     QXmlInputSource source(file);
     TypesHandler handler(this);
     xmlReader.setContentHandler(&handler);
     xmlReader.setErrorHandler(&handler);
     bool ok = xmlReader.parse(source);
     if (ok)  {
         m_loaded = true;
     } else {
         Q_ASSERT_X(false, "load", "types.xml parsing failed.");
     }
     delete file;
}

void NodeLibrary::unload()
{
}

Node* NodeLibrary::createNode(const QString& name)
{
    return nodeType(name)->createNode();
}

void NodeLibrary::addNodeType(NodeType* nodeType)
{
    m_types[nodeType->name()] = nodeType;
}

} // namespace NodeCore
