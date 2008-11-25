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

#ifndef ParameterType_h
#define ParameterType_h

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>

namespace NodeCore {

class Node;
class NodeType;
class OutputParameter;
class Parameter;

class MenuOption : public QObject {
    Q_OBJECT
public:
    MenuOption(const QString& key, const QString& label);
    MenuOption(const MenuOption& menuOption);
    QString key() const { return m_key; }
    QString label() const { return m_label; }
    MenuOption& operator=(const MenuOption& menuOption);
private:
    QString m_key;
    QString m_label;
};

class ParameterType : public QObject {
    Q_OBJECT
public:

    enum Direction {
        In,
        Out
    };

    enum CoreType {
        IntCoreType,
        DoubleCoreType,
        StringCoreType,
        DataCoreType
    };

    enum BoundingMethod {
        NoBounding,
        SoftBounding,
        HardBounding
    };

    ParameterType(NodeType* nodeType, const QString& name, const QString& type, Direction direction = In);
    virtual ~ParameterType();

    NodeType* nodeType() const { return m_nodeType; }
    QString name() const { return m_name; }
    QString label() const { return m_label; }
    void setLabel(const QString& label);
    QString description() const { return m_description; }
    void setDescription(const QString& description);
    QString type() const { return m_type; }
    Direction direction() const { return m_direction; }
    CoreType coreType() const { return m_coreType; }
    quint16 channels() const { return m_channels; }
    QVariantList defaultValues() const { return m_defaultValues; }
    BoundingMethod boundingMethod() const { return m_boundingMethod; }
    void setBoundingMethod(BoundingMethod method);
    QVariant minimumValue() const { return m_minimumValue; }
    void setMinimumValue(const QVariant& v);
    QVariant maximumValue() const { return m_maximumValue; }
    void setMaximumValue(const QVariant& v);
    bool isSingle() const { return m_channels == 1; }
    bool isInputParameter() const { return m_direction == In; }
    bool isOutputParameter() const { return m_direction == Out; }
    bool isCompatible(const Node* n) const;
    bool isCompatible(const NodeType* n) const;
    bool isCompatible(const OutputParameter* p) const;
    bool isCompatible(const ParameterType* p) const;
    void addMenuOption(const QString& key, const QString& label);

    bool validate(const QVariantList& v) const;
    Parameter* createParameter(Node* node);

private:
    void changeType(const QString& type);
    bool validateSingle(const QVariant& v) const;

private:
    NodeType* m_nodeType;
    QString m_name;
    QString m_label;
    QString m_description;
    QString m_type;
    CoreType m_coreType;
    quint16 m_channels;
    Direction m_direction;
    QVariantList m_defaultValues;
    QVariant m_minimumValue;
    QVariant m_maximumValue;
    BoundingMethod m_boundingMethod;
    QList<MenuOption> m_menuOptions;
};

} // namespace NodeCore

#endif // ParameterType_h
