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

#ifndef TypesHandler_h
#define TypesHandler_h

#include <QtXml/QXmlDefaultHandler>

#include "NodeCoreGlobal.h"
#include "NodeLibrary.h"
#include "NodeType.h"
#include "ParameterType.h"

namespace NodeCore {

class TypesHandler : public QXmlDefaultHandler {
public:
    TypesHandler(NodeLibrary* library);
    virtual ~TypesHandler();
    bool startDocument();
    bool startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& attrs);
    bool characters(const QString& characters);
    bool endElement (const QString& namespaceURI, const QString& localName, const QString& qName);
    bool endDocument();

    NodeLibrary* library() { return m_library; }
private:
    NodeLibrary* m_library;
    NodeType* m_nodeType;
    ParameterType* m_parameterType;
    bool m_inDescription;
};

} // namespace NodeCore

#endif // Connection_h
