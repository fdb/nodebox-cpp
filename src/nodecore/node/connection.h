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

#ifndef Connection_h
#define Connection_h

#include <qobject.h>

namespace NodeCore {
    
class Parameter;
class Node;

class Connection : public QObject {
    Q_OBJECT
public:
    Connection(Parameter *outputParameter, Parameter *inputParameter);
    virtual ~Connection();

    Parameter* outputParameter() const;
    Node* outputNode() const;
    Parameter* inputParameter() const;
    Node* inputNode() const;
    bool hasOutput() const;

    // friend std::ostream& operator<<(std::ostream& o, const Connection& c);

private:
    // Disallow copy construction or assignment
    Connection(const Connection& other);
    Connection& operator=(const Connection& other);
    
    void markDirtyDownstream();
    void update();
    
    Parameter* m_output;
    Parameter* m_input;
    
    friend class Parameter;
    friend class Node;
    friend class OutputParameter;
};

} // namespace NodeCore

#endif // Connection_h
