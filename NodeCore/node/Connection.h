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

#include <string>
#include <exception>
#include <iostream>

namespace NodeCore {
    
class Field;
class Node;

class ConnectionError : public std::exception {
public:
    ConnectionError(std::string message = "")
        :m_message(message) {}
    virtual ~ConnectionError() throw () {}
    std::string getMessage() { return m_message; }
private:
    std::string m_message;
};

class Connection {
public:
    Connection(Field *outputField, Field *inputField);
    virtual ~Connection();

    Field* getOutputField() const;
    Node* getOutputNode() const;
    Field* getInputField() const;
    Node* getInputNode() const;

    friend std::ostream& operator<<(std::ostream& o, const Connection& c);

private:
    // Disallow copy construction or assignment
    Connection(const Connection& other);
    Connection& operator=(const Connection& other);
    
    void markDirtyDownstream();
    void update();
    
    Field* m_output;
    Field* m_input;
    
    friend class Field;
};

} // namespace NodeCore

#endif // Connection_h
