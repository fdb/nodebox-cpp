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

#ifndef Node_h
#define Node_h

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QPointF>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include "OutputParameter.h"
#include "Parameter.h"

namespace NodeCore {

class Network;
class NodeType;
class OutputParameter;
class Parameter;

typedef QMap<QString, Parameter*> ParameterMap;
typedef QList<Parameter*> ParameterList;
typedef QList<Connection*> ConnectionList;
typedef ConnectionList::iterator ConnectionIterator;

class Node : public QObject {
    Q_OBJECT
public:
    Node(NodeType* type, const QString& name=NULL);
    virtual ~Node();

    // Basic attributes

    NodeType* nodeType() const { return m_type; }
    QPointF position() const { return QPointF(m_x, m_y); }
    void setPosition(const QPointF& p);
    qreal x() const { return m_x; }
    qreal y() const { return m_y; }
    void setX(qreal x);
    void setY(qreal y);
    OutputParameter* outputParameter() const { return m_outputParameter; }

    // Naming

    QString name() const { return m_name; }
    void setName(const QString& name);

    // Parameters

    Parameter* parameterAt(quint16 index) const { return parameters().at(index); }
    quint16 parameterCount() const { return m_parameters.count(); }
    QList<Parameter*> parameters() const;
    bool hasParameter(const QString& name) const { return m_parameters.contains(name); }

    // Value shortcuts

    QVariantList values(const QString& parameterName) const;
    void setValues(const QString& parameterName, const QVariantList& values);
    QVariantList outputValues() const;

    // Expression shortcuts

    // Connection shortcuts

    QList<Parameter*> compatibleParameters(Node* outputNode) const;
    bool disconnect();
    bool isConnected();

    // Node processing

    void update();
    void markDirty(bool forced=false);
    bool isDirty() const { return m_dirty; }
    QString error() const { return m_error; }
    bool hasError() const { return m_error.isEmpty(); }

    // Network state

    Network* network() const { return m_network; }
    void setNetwork(Network* network);
    Network* rootNetwork() const;
    bool inNetwork() const { return m_network != NULL; }
    bool isRendered() const;
    void setRendered();
    QString networkPath();

    // Reloading

    void reload();
    
protected:
    void reloadEvent();
    virtual bool process();
    void setOutputValues(const QVariantList& values);
    void setError(const QString& error);
    
private:
    NodeType* m_type;
    Network* m_network;
    QString m_name;
    qreal m_x, m_y;
    QString m_error;
    bool m_dirty;
    QMap<QString, Parameter*> m_parameters;
    OutputParameter* m_outputParameter;

    friend class Network;
};

} // namespace NodeCore

#endif // Node_h
