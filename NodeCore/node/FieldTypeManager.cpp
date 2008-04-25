#include "NodeCore.h"

namespace NodeCore {

void FieldTypeManager::addFieldType(FieldType name, FieldInitializer initializer)
{ 
    getFieldTypeMap()[name] = initializer;
}

FieldInitializer FieldTypeManager::getInitializer(FieldType name) {
    FieldTypeMap ftm = getFieldTypeMap();
    if (ftm.empty()) {
        std::cout << "Initializing the basics." << std::endl;
        // Initialize the basics
        addFieldType("core/int", IntField::initialize);
        addFieldType("core/float", FloatField::initialize);
        addFieldType("core/string", StringField::initialize);
    }
    // TODO: The map size should be 3, but it isn't.
    std::cout << "new map size " << ftm.size() << std::endl;
    return ftm[name];
}

Field* FieldTypeManager::initialize(FieldType type, Node *node, FieldName name, FieldPolarity polarity) {
    FieldInitializer init; //  = getInitializer(type);    
    // TODO: Use the map. The map always remains at size 0 -- why?
    if (type == "core/int") {
        init = IntField::initialize;
    } else if (type == "core/float") {
        init = FloatField::initialize;
    } else if (type == "core/string") {
        init = StringField::initialize;
    } else {
        throw FieldTypeNotFound(type);
    }
    Field* f = (*init)(node, name, polarity);
    return f;
}
    
FieldTypeMap FieldTypeManager::getFieldTypeMap() {
    static FieldTypeMap m_typeMap = FieldTypeMap();
    return m_typeMap;
}

} // namespace NodeCore