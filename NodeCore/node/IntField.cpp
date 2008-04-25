#include <boost/lexical_cast.hpp>

#include "NodeCore.h"

namespace NodeCore {

IntField::IntField(Node *node, FieldName name, FieldPolarity polarity)
        : Field(node, name, polarity), m_value(0)
{
}

IntField::~IntField()
{
}

int IntField::asInt()
{
    return m_value;
}

float IntField::asFloat()
{
    return boost::lexical_cast<float>(m_value);
}

std::string IntField::asString()
{
    return boost::lexical_cast<std::string>(m_value);
}

void IntField::set(int i)
{
    preSet();
    m_value = i;
    postSet();
}

void IntField::set(float f)
{
    preSet();
    m_value = (int) f;
    postSet();
}

void IntField::set(std::string s)
{
    preSet();
    m_value = boost::lexical_cast<int>(s);
    postSet();
}

void IntField::revertToDefault()
{
    m_value = 0;
}

void IntField::setValueFromConnection()
{
    assert(isConnected());
    m_value = getConnection()->getOutputField()->asInt();
}

} // namespace NodeCore