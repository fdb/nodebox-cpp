#ifndef FieldTypeManager_h
#define FieldTypeManager_h

#include "Field.h"

#include <string>
#include <map>
#include <iostream>

namespace NodeCore {

class Field;
class Node;

typedef Field* (*FieldInitializer)(Node *node, FieldName name, FieldPolarity polarity);
typedef std::map<std::string, FieldInitializer> FieldTypeMap;

class FieldTypeNotFound {
public:
    FieldTypeNotFound(FieldType type) : m_type(type) {}
    FieldType getFieldType() { return m_type; }
private:
    FieldType m_type;
};

class FieldTypeManager {
public:

    static void addFieldType(FieldType name, FieldInitializer initializer);
    
    static FieldInitializer getInitializer(FieldType name);
    static Field* initialize(FieldType type, Node *node, FieldName name, FieldPolarity polarity = kIn);
    
private:
    static FieldTypeMap getFieldTypeMap();
};


} // namespace NodeCore

#endif // FieldTypeManager_h
