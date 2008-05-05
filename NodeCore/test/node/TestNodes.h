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

#ifndef TestNodes_h
#define TestNodes_h

#include <NodeCore/NodeCore.h>

using namespace NodeCore;

class IntNode : public Node
{
public:
    IntNode() : m_output(0) {} 
    int getOutput() { return m_output; }
    virtual bool canConnectTo(Field* f) const
    {
        return f->getType() == kInt;
    }
protected:
    void setOutput(int i) { m_output = i; }
    virtual void updateField(Field* f)
    {
        assert (f->getType() == kInt);
        f->set(m_output);
    }
private:
    int m_output;
};

class NumberGenerator : public IntNode
{
public:
    NumberGenerator()
    {
        addField("number", kInt);
    }

protected:
    virtual void process()
    {
        int number = asInt("number");
        setOutput(number);
    }
    NodeNameMacro(NumberGenerator);
};

class Multiplier : public IntNode
{
public:
    Multiplier()
    {
        addField("number", kInt);
        addField("multiplier", kInt);
        addField("somestring", kString);
    }
protected:
    virtual void process()
    {
        // Fails for big numbers
        int number = asInt("number");
        int multiplier = asInt("multiplier");
        setOutput(number * multiplier);
    }
    NodeNameMacro(Multiplier);
};

class ValueNode : public Node {
public:
    ValueNode() {
        f_int = addField("int", kInt);
        f_float = addField("float", kFloat);
        f_string = addField("string", kString);
    }
    virtual ~ValueNode() {}

protected:
    virtual void process() { }

public:
    Field *f_int;
    Field *f_float;
    Field *f_string;

    NodeNameMacro(ValueNode);
};

#endif // TestNodes_h