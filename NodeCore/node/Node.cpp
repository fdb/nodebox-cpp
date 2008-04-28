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

#include "config.h"
#include "Node.h"
//#include <boost/regex.hpp>

#include "FieldTypeManager.h"

namespace NodeCore {

Node::Node()
    :
    m_x(0),
    m_y(0),
    m_name(""), // This should go to defaultName(), but you can't call virtuals in ctors.
    m_dirty(true)
{
}

Node::~Node()
{
}

std::string Node::getName()
{
    // The name "" is set from the constructor.
    // If the name is asked for the first name, it will be set
    // to the correct name, e.g. the default name.
    if (m_name == "") {
        m_name = defaultName();
    }
    return m_name;
}

void Node::setName(const NodeName& name)
{
    if (validName(name)) {
        m_name = name;
    } else {
        throw InvalidName();
    }
}

bool Node::validName(const NodeName& name)
{
    regex_t nameRe, doubleUnderScoreRe;

    // Only lowercase letters, digits and underscore. Start with letter or underscore.
    // Minimum 1 characters, maximum 30 characters.
    regcomp(&nameRe, "^[a-z_][a-z0-9_]{0,29}$", REG_EXTENDED|REG_NOSUB);

    // No double underscore names (__reserved)
    regcomp(&doubleUnderScoreRe, "^__.*$", REG_EXTENDED|REG_NOSUB);

    return regexec(&nameRe, name.c_str(), 0, NULL, 0) == 0 &
           regexec(&doubleUnderScoreRe, name.c_str(), 0, NULL, 0) != 0;
}

Field* Node::addField(const FieldName &name, FieldType type, FieldPolarity polarity)
{
    if (hasField(name)) { throw InvalidName(); }
    Field *f = FieldTypeManager::initialize(type, this, name, polarity);
//new Field(this, name, type, polarity);
    m_fields[name] = f;
    return f;
}

Field* Node::getField(const FieldName &name)
{
    if (hasField(name)) {
        Field* f = m_fields[name];
        return f;
    } else {
        throw FieldNotFound(name);
    }
}

bool Node::hasField(const FieldName &name)
{
    return m_fields.count(name) == 1;
}

/**
 * Returns the first output field.
 */
Field* Node::getOutputField()
{
    m_fields.begin();
    for(FieldIterator iter=m_fields.begin(); iter != m_fields.end(); iter++) {
        Field *f = (*iter).second;
        if (f->getPolarity() & kOut) { // Matches kOut and kInOut
            return f;
        }
    }
    return NULL;
}

// Value shortcuts
int Node::asInt(const FieldName &name)
{
    return getField(name)->asInt();
}

float Node::asFloat(const FieldName &name)
{
    return getField(name)->asFloat();
}

std::string Node::asString(const FieldName &name)
{
    return getField(name)->asString();
}

void Node::set(const FieldName &name, int i)
{
    getField(name)->set(i);
}

void Node::set(const FieldName &name, float f)
{
    getField(name)->set(f);
}

void Node::set(const FieldName &name, std::string s)
{
    getField(name)->set(s);
}

void Node::update()
{
    if (m_dirty) {
        // Update all input fields so values are up to date.
        for (FieldIterator iter = m_fields.begin(); iter != m_fields.end(); ++iter) {
            Field* f = (*iter).second;
            if (f->m_polarity == kIn) {
                f->update();
            }
        }
        process();
        m_dirty = false;
    }
}

bool Node::isDirty()
{
    return m_dirty;
}

void Node::markDirty()
{
    m_dirty = true;
    getOutputField()->markDirty();
    // TODO: make network dirty
    // TODO: dispatch/notify
}

void Node::process()
{
    // This space intentionally left blank.
}

std::ostream& operator<<(std::ostream& o, const Node& n)
{
    o << "Node(" << n.m_name << ")";
    return o;
}

} // namespace NodeCore