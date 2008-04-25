#include <boost/lexical_cast.hpp>

#include "NodeCore.h"

namespace NodeCore {

FloatField::FloatField(Node *node, FieldName name, FieldPolarity polarity)
        : Field(node, name, polarity), m_value(0)
{
}

FloatField::~FloatField()
{
}

int FloatField::asInt()
{
    return boost::lexical_cast<int>(m_value);
}

float FloatField::asFloat()
{
    return m_value;
}

std::string FloatField::asString()
{
    return boost::lexical_cast<std::string>(m_value);
}

void FloatField::set(int i)
{
    preSet();
    m_value = (float) i;
    postSet();
}

void FloatField::set(float f)
{
    preSet();
    m_value = f;
    postSet();
}

void FloatField::set(std::string s)
{
    preSet();
    m_value = boost::lexical_cast<float>(s);
    postSet();
}

void FloatField::revertToDefault()
{
    m_value = 0;
}

void FloatField::setValueFromConnection()
{
    assert(isConnected());
    m_value = getConnection()->getOutputField()->asFloat();
}

} // namespace NodeCore