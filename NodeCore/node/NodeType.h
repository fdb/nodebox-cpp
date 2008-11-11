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

#ifndef NodeType_h
#define NodeType_h

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "NodeCoreGlobal.h"

namespace NodeCore {

class ParameterType;
class Node;
class NodeLibrary;

class NODECORESHARED_EXPORT NodeType : public QObject {
    Q_OBJECT
public:
    NodeType(NodeLibrary* library, const QString& name, const QString& outputType, const QString& methodName);
    virtual ~NodeType();

    static bool isValidName(const QString& name);

    // Basic attributes
    QString name() const { return m_name; }
    QString defaultName() const { return m_name; }
    QString label() const { return m_label; }
    QString description() const { return m_description; }
    void setDescription(const QString& description);

    QString methodName() const { return m_methodName; }
    void setMethodName(const QString& methodName);
    void reload();

    // Parameters
    ParameterType* addParameter(const QString& name, const QString& type);
    QList<ParameterType*> parameterTypes() const { return m_parameterTypes; }
    ParameterType* parameterTypeAt(quint16 index) const { return m_parameterTypes.at(index); }
    int parameterTypeCount() const { return m_parameterTypes.count(); }
    ParameterType* outputParameterType() const { return m_outputParameterType; }

    Node* createNode(const QString& name=NULL);

private:
    NodeLibrary* m_library;
    QString m_name;
    QString m_label;
    QString m_description;
    ParameterType* m_outputParameterType;
    QList<ParameterType*> m_parameterTypes;
    QString m_methodName;
};

} // namespace NodeCore

#endif // NodeType_h
