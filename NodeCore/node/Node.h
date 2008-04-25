#ifndef Node_h
#define Node_h

#include "Field.h"

#include <vector>
#include <string>
#include <map>

namespace NodeCore {

typedef std::map<std::string, Field*> FieldMap;
typedef FieldMap::iterator FieldIterator;

#define NodeNameMacro(nodeName) \
public: \
    static Node* initialize() { return new nodeName; } \
    virtual std::string className() { return #nodeName; }

// TODO: forbidden names

class Node {
public:
    Node();
    virtual ~Node();
    
    virtual NodeName defaultName() { return className(); };

    Field* addField(const FieldName &name, FieldType type, FieldPolarity polarity=kIn);
    Field* getField(const FieldName &name);
    bool hasField(const FieldName &name);
    Field* getOutputField();
    
    // Value shortcuts
    int asInt(const FieldName &name);
    float asFloat(const FieldName &name);
    std::string asString(const FieldName &name);

    // All these can throw a ValueError.
    void set(const FieldName &name, int i);
    void set(const FieldName &name, float f);
    void set(const FieldName &name, std::string s);
    
    NodeName getName();
    void setName(const NodeName &name);
    static bool validName(const NodeName& name);
    
    
    void update();
    bool isDirty();
    void markDirty();

    friend std::ostream& operator<<(std::ostream& o, const Node& n);
    
protected:
    virtual void process();
    
private:
    float m_x, m_y;
    std::string m_name;
    FieldMap m_fields;
    // TODO: add exception
    bool m_dirty;

    NodeNameMacro(Node);
};

} // namespace NodeCore

#endif // Node_h
