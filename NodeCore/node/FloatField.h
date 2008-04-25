#ifndef FloatField_h
#define FloatField_h

#include <string>

#include "Field.h"

namespace NodeCore {

class FloatField : public Field {
public:
    FloatField(Node *node, FieldName name, FieldPolarity polarity = kIn);
    virtual ~FloatField();

    virtual int asInt();
    virtual float asFloat();
    virtual std::string asString();
    
    virtual void set(int i);
    virtual void set(float f);
    virtual void set(std::string s);

    virtual std::string getTypeName() { return "core/float"; }

protected:
    virtual void revertToDefault();
    virtual void setValueFromConnection();

private:
    float m_value;

    FieldTypeMacro(FloatField);
};

} // namespace NodeCore

#endif // FloatField_h
