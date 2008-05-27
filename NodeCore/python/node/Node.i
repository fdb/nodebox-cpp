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

typedef std::map<std::string, Field*> FieldMap;
typedef FieldMap::iterator FieldMapIterator;

typedef std::string NodeName;
typedef std::string NodeType;

class Network;

typedef std::vector<Field*> FieldList;
typedef FieldList::iterator FieldIterator;
typedef std::vector<Connection*> ConnectionList;
typedef ConnectionList::iterator ConnectionIterator;

%feature("director") Node;
class Node {
public:
    Node(const FieldType& outputType = kInt);
    virtual ~Node();
    
    virtual NodeName defaultName() const;
    
    NodeName getName() const;
    void setName(const NodeName &name);
    static bool validName(const NodeName& name);
    
    void setNetwork(Network* network);
    Network* getNetwork();
        
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    void setX(float x);
    void setY(float y);

    Field* addField(const FieldName &name, const FieldType& type);
    Field* getField(const FieldName &name) const;
    bool hasField(const FieldName &name) const;
    Field* getOutputField() const { return m_outputField; }
    FieldType getOutputType() const { return m_outputField->getType(); }
    FieldList getFields();
    
    // Value shortcuts
    int asInt(const FieldName &name);
    float asFloat(const FieldName &name);
    std::string asString(const FieldName &name);
    void* asData(const FieldName &name);
    
    // All these can throw a ValueError.
    void set(const FieldName &name, int i);
    void set(const FieldName &name, float f);
    void set(const FieldName &name, const std::string& s);
    void set(const FieldName &name, void* d);
    
    void update();
    bool isDirty() const;
    void markDirty();
    
    bool isOutputConnected();
    bool isOutputConnectedTo(Node* node);
    bool isOutputConnectedTo(Field* field);
    ConnectionList getOutputConnections();

    int outputAsInt() const;
    float outputAsFloat() const;
    std::string outputAsString() const;
    void* outputAsData() const;

    void _setOutput(int i);
    void _setOutput(float f);
    void _setOutput(std::string s);
    void _setOutput(void* d);
    // Needed for setOutput overrides
    void _setOutputAsData(void* d) { setOutput(d); }
    
protected:
    virtual void process();
};

} // namespace NodeCore
