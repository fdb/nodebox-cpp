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
#include "NodeType.h"
#include "ParameterType.h"

#include <QtCore/QRegExp>

namespace NodeCore {

NodeType::NodeType(NodeLibrary* library, const QString& name, const QString& outputType, const QString& methodName)
    : m_library(library),
      m_name(name),
      m_methodName(methodName)
{
    // TODO: Check if name is valid
    isValidName(name);
    m_outputParameterType = new ParameterType(this, QString("output"), outputType, ParameterType::Out);
}

NodeType::~NodeType()
{
    delete m_outputParameterType;
    disconnect();
}

bool NodeType::isValidName(const QString& name)
{
    // Only lowercase letters, digits and underscore. Start with letter or underscore.
    // Minimum 1 characters, maximum 30 characters.
    QRegExp nameRe = QRegExp(QString("^[a-z_][a-z0-9_]{0,29}$"));

    // No double underscore names (__reserved)
    QRegExp doubleUnderScoreRe = QRegExp(QString("^__.*$"));

    // No reserved words
    QRegExp reservedRe = QRegExp(QString("^(node|name)$"));

    return nameRe.exactMatch(name) &
            !doubleUnderScoreRe.exactMatch(name) &
            !reservedRe.exactMatch(name);
}

ParameterType* NodeType::addParameter(const QString& name, const QString& type)
{
    ParameterType* pType = new ParameterType(this, name, type);
    m_parameterTypes.append(pType);
    return pType;
}

void NodeType::setDescription(const QString& description)
{
    m_description = description;
}

void NodeType::setMethodName(const QString& methodName)
{
    // Check if processing method is in NodeLibrary
    m_methodName = methodName;
    // Check if processing method is callable in the NodeLibrary
}

void NodeType::reload()
{
    // TODO: Do the actual reloading
}

Node* NodeType::createNode(const QString& name)
{
    return new Node(this, name);
}

} // namespace NodeCore
