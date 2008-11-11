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

#ifndef OutputParameter_h
#define OutputParameter_h

#include <QtCore/QString>
#include <QtCore/QVariant>

#include "NodeCoreGlobal.h"
#include "Parameter.h"

namespace NodeCore {

class Connection;
class Node;
class ParameterType;

class NODECORESHARED_EXPORT OutputParameter : public Parameter {
    Q_OBJECT
public:
    OutputParameter(ParameterType* type, Node* node);
    virtual ~OutputParameter();

    virtual bool isOutputParameter() const { return true; }

    virtual void setValues(const QVariantList&) { }

    virtual Connection* connect(Node*) { return NULL; }
    virtual bool disconnect() { return false; }
    virtual bool isConnected() const { return m_downstreams.count() != 0; }
    virtual bool canConnect(const Node*) { return false; }
    virtual bool canConnect(const OutputParameter*) { return false; }

    virtual bool validate(const QVariantList&) { return false; }

    void markDirtyDownstream();
    void copyWithUpstream();

private:
    // TODO: Should be a QSet
    QList<Connection*> m_downstreams;

    friend class Node;
    friend class Parameter;
};

} // namespace NodeCore

#endif // OutputParameter_h
