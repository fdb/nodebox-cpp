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

typedef std::map<std::string, Parameter*> ParameterMap;
typedef ParameterMap::iterator ParameterMapIterator;

typedef std::string NodeName;
typedef std::string NodeType;

class Network;

typedef std::vector<Parameter*> ParameterList;
typedef ParameterList::iterator ParameterIterator;
typedef std::vector<Connection*> ConnectionList;
typedef ConnectionList::iterator ConnectionIterator;

%feature("director") Node;
class Node {
public:
    Node(const ParameterType& outputType = kInt);
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

    Parameter* addParameter(const ParameterName &name, const ParameterType& type);
    Parameter* getParameter(const ParameterName &name) const;
    bool hasParameter(const ParameterName &name) const;
    Parameter* getOutputParameter() const { return m_outputParameter; }
    ParameterType getOutputType() const { return m_outputParameter->getType(); }
    ParameterList getParameters();
    
    // Value shortcuts
    int asInt(const ParameterName &name);
    float asFloat(const ParameterName &name);
    std::string asString(const ParameterName &name);
    void* asData(const ParameterName &name);
    
    // All these can throw a ValueError.
    void set(const ParameterName &name, int i);
    void set(const ParameterName &name, float f);
    void set(const ParameterName &name, const std::string& s);
    void set(const ParameterName &name, void* d);
    
    void update();
    bool isDirty() const;
    void markDirty();
    
    bool isOutputConnected();
    bool isOutputConnectedTo(Node* node);
    bool isOutputConnectedTo(Parameter* parameter);
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
