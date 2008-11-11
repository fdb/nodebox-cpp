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

#ifndef Parameter_h
#define Parameter_h

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtScript/QScriptValue>

#include "NodeCoreGlobal.h"
#include "ParameterType.h"

namespace NodeCore {

class Connection;
class OutputParameter;
class ParameterType;
class Node;

class NODECORESHARED_EXPORT Parameter : public QObject {
    Q_OBJECT
public:
    Parameter(ParameterType* type, Node* node);
    virtual ~Parameter();

    ParameterType* parameterType() const { return m_type; }
    virtual bool isOutputParameter() const { return false; }
    bool isInputParameter() const { return !isOutputParameter(); }
    Node* node() const { return m_node; }
    QString name() const { return m_type->name(); }

    QVariantList values() const { return m_values; }
    virtual void setValues(const QVariantList& values);
    virtual bool validate(const QVariantList& values);
    virtual void revertToDefault();

    QString expression() const { return m_expression; }
    void setExpression(const QString& s);
    bool hasExpression() const { return m_expression.isEmpty(); }
    void clearExpression();
    QList<Parameter*> expressionDependencies() const;

    virtual Connection* connect(Node* node);
    virtual bool disconnect();
    virtual bool isConnected() const { return m_connection != NULL; }
    virtual bool canConnect(const Node* node) const;
    virtual bool canConnect(const OutputParameter* p) const;

    void update();

private:
    QList<QScriptValue*> expressionLocals();
    QList<QScriptValue*> expressionGlobals();
    QVariantList evaluateExpression();
    void createExpressionConnections();
    void removeExpressionConnections();

    ParameterType* m_type;
    Node* m_node;
    QVariantList m_values;
    Connection* m_connection;
    QString m_expression;
    QList<Connection*> m_expressionConnections;

    friend class Node;
};

} // namespace NodeCore

#endif // Parameter_h
