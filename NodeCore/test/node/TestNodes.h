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

class NumberGenerator : public Node
{
public:
    NumberGenerator() : Node(kInt)
    {
        addField("number", kInt);
    }

protected:
    virtual void process()
    {
        int number = asInt("number");
        _setOutput(number);
    }
    NodeNameMacro(NumberGenerator);
};

class Multiplier : public Node
{
public:
    Multiplier() : Node(kInt)
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
        _setOutput(number * multiplier);
    }
    NodeNameMacro(Multiplier);
};

class ValueNode : public Node {
public:
    ValueNode() : Node(kInt)
    {
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