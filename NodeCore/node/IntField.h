#ifndef IntField_h
#define IntField_h

#include <string>

#include "Field.h"

namespace NodeCore {

class IntField : public Field {
public:
    IntField(Node *node, FieldName name, FieldPolarity polarity = kIn);
    virtual ~IntField();
    
    virtual int asInt();
    virtual float asFloat();
    virtual std::string asString();
    
    virtual void set(int i);
    virtual void set(float f);
    virtual void set(std::string s);
    
    virtual std::string getTypeName() { return "core/int"; }

protected:
    virtual void revertToDefault();
    virtual void setValueFromConnection();

private:
    int m_value;

    FieldTypeMacro(IntField);
};

} // namespace NodeCore

#endif // IntField_h
