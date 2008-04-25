#include <boost/lexical_cast.hpp>

#include "NodeCore.h"

namespace NodeCore {

StringField::StringField(Node *node, FieldName name, FieldPolarity polarity)
            : Field(node, name, polarity)
{
}

StringField::~StringField()
{
}

int StringField::asInt()
{
    return boost::lexical_cast<int>(m_value);
}

float StringField::asFloat()
{
    return boost::lexical_cast<float>(m_value);
}

std::string StringField::asString()
{
    return m_value;
}

void StringField::set(int i)
{
    preSet();
    m_value = boost::lexical_cast<std::string>(i);
    postSet();
}

void StringField::set(float f)
{
    preSet();
    m_value = boost::lexical_cast<std::string>(f);
    postSet();
}

void StringField::set(std::string s)
{
    preSet();
    m_value = s;
    postSet();
}

void StringField::revertToDefault()
{
    m_value = "";
}

void StringField::setValueFromConnection()
{
    assert(isConnected());
    m_value = getConnection()->getOutputField()->asString();
}

} // namespace NodeCore