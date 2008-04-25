#ifndef StringField_h
#define StringField_h

#include <string>

#include "Field.h"

namespace NodeCore {

class StringField : public Field {
public:
    StringField(Node *node, FieldName name, FieldPolarity polarity = kIn);
    virtual ~StringField();

    virtual int asInt();
    virtual float asFloat();
    virtual std::string asString();
    
    virtual void set(int i);
    virtual void set(float f);
    virtual void set(std::string s);
    
    virtual std::string getTypeName() { return "core/string"; }

protected:
    virtual void revertToDefault();
    virtual void setValueFromConnection();

private:
    std::string m_value;

    FieldTypeMacro(StringField);
};

} // namespace NodeCore

#endif // StringField_h
