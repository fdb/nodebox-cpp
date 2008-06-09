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

namespace NodeCore {

class Node;

typedef std::string ParameterName;
typedef std::string ParameterType;

const ParameterType kInt = "int";
const ParameterType kFloat = "float";
const ParameterType kString = "string";
const ParameterType kNode = "Node";
const ParameterType kNetwork = "Network";

enum ParameterDirection {
    kIn = 1,
    kOut = 2
};

class Parameter {
public:
    Parameter(Node *node, const ParameterName& name, const ParameterType& type, ParameterDirection dir = kIn);
    virtual ~Parameter();
    
    Node* getNode() const { return m_node; }
    ParameterDirection getDirection() const { return m_direction; }
    bool isInputParameter() const { return m_direction == kIn; }
    bool isOutputParameter() const { return m_direction == kOut; }
    
    int asInt();
    float asFloat();
    std::string asString();
    void* asData();

    // All these can throw a ValueError.
    void set(int i);
    void set(float f);
    void set(const std::string& s);
    void set(void* v);
    
    ParameterName getName() const { return m_name; }
    ParameterType getType() const { return m_type; }
    
    // Connection methods
    bool canConnectTo(Node* node);
    Connection* connect(Node* node);
    bool disconnect();
    bool isConnected();
    bool isConnectedTo(Node* node);
    Connection* getConnection();
    void update();
    
    static bool validName(const ParameterName& name);
    
protected:
    void revertToDefault();
    void preSet();
    void postSet();
    
private:
    union Value {
        int i;
        float f;
        std::string* s;
        void* d;
    };

    // Disallow copy construction or assignment
    Parameter(const Parameter& other);
    Parameter& operator=(const Parameter& other);

    void markDirty();

    Node *m_node;
    std::string m_name;
    std::string m_verboseName;
    ParameterType m_type;
    ParameterDirection m_direction;
    Connection *m_connection;
    Value m_value;
    // TODO: expression
    
    friend class Node;
};

} // namespace NodeCore
