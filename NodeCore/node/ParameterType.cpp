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
#include "OutputParameter.h"
#include "Parameter.h"
#include "ParameterType.h"

namespace NodeCore {

MenuOption::MenuOption(const QString& key, const QString& label)
    : m_key(key),
      m_label(label)
{
}

MenuOption::MenuOption(const MenuOption& menuOption)
    : QObject(),
      m_key(menuOption.m_key),
      m_label(menuOption.m_label)
{
}

MenuOption& MenuOption::operator=(const MenuOption& menuOption)
{
    m_key = menuOption.m_key;
    m_label = menuOption.m_label;
    return *this;
}

ParameterType::ParameterType(NodeType* nodeType, const QString& name, const QString& type, Direction direction)
    : m_nodeType(nodeType),
      m_name(name),
      m_type(type),
      m_direction(direction)
{
    m_label = name;
    m_description = QString();
    changeType(type);
}

ParameterType::~ParameterType()
{
}

void ParameterType::setLabel(const QString& label)
{
    m_label = label;
}

void ParameterType::setDescription(const QString& description)
{
    m_description = description;
}

void ParameterType::setBoundingMethod(BoundingMethod method)
{
    m_boundingMethod = method;
}

void ParameterType::setMinimumValue(const QVariant& v)
{
    m_minimumValue = v;
}


void ParameterType::setMaximumValue(const QVariant& v)
{
    m_maximumValue = v;
}

/*! Returns whether this type is compatible with the given output Node type.

    All this does is compare my type with the output parameter type of the given node.

    The check is very strict. The two types have to match exactly. In the future, we might
    loosen this constraint to also accept types with the same core type and number of channels.
*/
bool ParameterType::isCompatible(const Node* n) const
{
    ParameterType* t = n->outputParameter()->parameterType();
    return isCompatible(t);
}

/*! Returns whether this type is compatible with the given output Node type.

    All this does is compare my type with the parameter type of the given parameter.

    The check is very strict. The two types have to match exactly. In the future, we might
    loosen this constraint to also accept types with the same core type and number of channels.
*/
bool ParameterType::isCompatible(const NodeType* n) const
{
    ParameterType* t = n->outputParameterType();
    return isCompatible(t);
}

/*! Returns whether this type is compatible with the given output Parameter.

    All this does is compare my type with the parameter type of the given parameter.

    The check is very strict. The two types have to match exactly. In the future, we might
    loosen this constraint to also accept types with the same core type and number of channels.
*/
bool ParameterType::isCompatible(const OutputParameter* p) const
{
    ParameterType* t = p->parameterType();
    return isCompatible(t);
}

/*! Returns whether this type is compatible with the given output Parameter type.

    All this does is compare my type with the parameter type of the given parameter.

    The check is very strict. The two types have to match exactly. In the future, we might
    loosen this constraint to also accept types with the same core type and number of channels.
*/
bool ParameterType::isCompatible(const ParameterType* p) const
{
    return m_type == p->type();
}

void ParameterType::addMenuOption(const QString& key, const QString& label)
{
    m_menuOptions.append(MenuOption(key, label));
}

bool ParameterType::validate(const QVariantList& values) const
{
    if (isSingle()) {
        return validateSingle(values.first());
    } else {
        for (int i = 0; i < values.size(); ++i) {
            const QVariant& v = values.at(i);
            if (validateSingle(v))
                return false;
        }
        return true;
    }
}

void ParameterType::changeType(const QString& type)
{
    // TODO: Create a type registry
    if (type == "angle") {
        m_coreType = ParameterType::DoubleCoreType;
    }
}

bool ParameterType::validateSingle(const QVariant& v) const
{
    // Check if we can cast the given variant to the correct type.
    // The data core type can have any type.
    if (
        (m_coreType == IntCoreType && !v.canConvert(QVariant::Int)) ||
        (m_coreType == DoubleCoreType && !v.canConvert(QVariant::Double)) ||
        (m_coreType == StringCoreType && !v.canConvert(QVariant::String))) {
        return false;
    }

    // If hard bounds are set, check if the value falls within the bounds.
    if (m_boundingMethod == HardBounding) {
        /* TODO: Compare QVariants
        if (
            (!m_minimumValue.isNull() && v < m_minimumValue) ||
            (!m_maximumValue.isNull() && v > m_maximumValue)) {
            return false;
        }
        */
    }

    return true;
}

Parameter* ParameterType::createParameter(Node* node)
{
    if (isInputParameter()) {
        return new Parameter(this, node);
    } else {
        return new OutputParameter(this, node);
    }
}

} // namespace NodeCore
