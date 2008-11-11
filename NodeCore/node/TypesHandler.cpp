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

#include <QtCore/QString>

#include "NodeLibrary.h"
#include "NodeType.h"
#include "ParameterType.h"
#include "TypesHandler.h"

namespace NodeCore {

TypesHandler::TypesHandler(NodeLibrary* library)
    : m_library(library),
      m_nodeType(NULL),
      m_parameterType(NULL),
      m_inDescription(false)
{
}

TypesHandler::~TypesHandler()
{
}

bool TypesHandler::startDocument()
{
    return true;
}

bool TypesHandler::endDocument()
{
    return true;
}

bool TypesHandler::startElement(const QString&, const QString&, const QString& qName, const QXmlAttributes& attrs)
{
    if (qName == "library") {
        m_library->setLabel(attrs.value("label"));
        QString type = attrs.value("type");
        if (type == "native") {
            m_library->setLibraryType(NodeLibrary::NativeType);
        } else if (type == "python") {
            m_library->setLibraryType(NodeLibrary::PythonType);
        } else {
            Q_ASSERT_X(false, "startElement", "Unknown library type");
            return false;
        }
    } else if (qName == "type") {
        Q_ASSERT(m_nodeType == NULL);
        QString name = attrs.value("name");
        QString outputType = attrs.value("ouputType");
        QString methodName = attrs.value("method");
        m_nodeType = new NodeType(m_library, name, outputType, methodName);
        m_library->addNodeType(m_nodeType);
    } else if (qName == "parameter") {
        Q_ASSERT(m_nodeType != NULL);
        Q_ASSERT(m_parameterType == NULL);
        QString name = attrs.value("name");
        QString type = attrs.value("type");
        m_parameterType = m_nodeType->addParameter(name, type);
        if (attrs.index("label") >= 0)
            m_parameterType->setLabel(attrs.value("label"));
        if (attrs.index("description") >= 0)
            m_parameterType->setDescription(attrs.value("description"));
        if (attrs.index("bounding") >= 0) {
            QString bounding = attrs.value("bounding");
            if (bounding == "none") {
                m_parameterType->setBoundingMethod(ParameterType::NoBounding);
            } else if (bounding == "soft") {
                m_parameterType->setBoundingMethod(ParameterType::SoftBounding);
            } else if (bounding == "hard") {
                m_parameterType->setBoundingMethod(ParameterType::HardBounding);
            }
        }
        if (attrs.index("minimum") >= 0) {
            if (m_parameterType->coreType() == ParameterType::IntCoreType) {
                int minimum = attrs.value("minimum").toInt();
                m_parameterType->setMinimumValue(QVariant(minimum));
            } else if (m_parameterType->coreType() == ParameterType::DoubleCoreType) {
                double minimum = attrs.value("minimum").toDouble();
                m_parameterType->setMinimumValue(QVariant(minimum));
            }
        }
        if (attrs.index("maximum") >= 0) {
            if (m_parameterType->coreType() == ParameterType::IntCoreType) {
                int maximum = attrs.value(maximum).toInt();
                m_parameterType->setMaximumValue(QVariant(maximum));
            } else if (m_parameterType->coreType() == ParameterType::DoubleCoreType) {
                double maximum = attrs.value("maximum").toDouble();
                m_parameterType->setMaximumValue(QVariant(maximum));
            }
        }
    } else if (qName == "option") {
        Q_ASSERT(m_parameterType != NULL);
        Q_ASSERT(m_parameterType->type() == "menu");
        m_parameterType->addMenuOption(attrs.value("key"), attrs.value("label"));
    } else if (qName == "description") {
        Q_ASSERT(m_nodeType != NULL);
        Q_ASSERT(m_parameterType == NULL);
        Q_ASSERT(!m_inDescription);
    } else {
        QString msg("Unknown element ");
        msg.append(qName);
        Q_ASSERT_X(false, "startElement", msg.toLocal8Bit().constData());
    }
    return true;
}

bool TypesHandler::characters(const QString& characters)
{
    Q_ASSERT(m_inDescription);
    QString description = m_nodeType->description() + characters;
    m_nodeType->setDescription(description.trimmed());
    return true;
}

bool TypesHandler::endElement (const QString&, const QString&, const QString& qName)
{
    if (qName == "library") {
        Q_ASSERT(m_library != NULL);
    } else if (qName == "type") {
        Q_ASSERT(m_nodeType != NULL);
        m_nodeType = NULL;
    } else if (qName == "parameter") {
        Q_ASSERT(m_parameterType != NULL);
        m_parameterType = NULL;
    } else if (qName == "option") {
        Q_ASSERT(m_parameterType != NULL);
    } else if (qName == "description") {
        Q_ASSERT(m_inDescription);
        m_inDescription = false;
    } else {
        QString msg("Unknown element ");
        msg.append(qName);
        Q_ASSERT_X(false, "endElement", msg.toLocal8Bit().constData());
    }
    return true;
}

} // namespace NodeCore
