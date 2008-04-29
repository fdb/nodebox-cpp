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

using namespace NodeCore;

#include <NodeCore/NodeCore.h>

using namespace NodeCore;

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

class FieldTestSuite : public Test::Suite
{
public:
	FieldTestSuite()
	{
		TEST_ADD(FieldTestSuite::test_values);
	}

private:
    void test_values()
    {
        ValueNode *n = new ValueNode();

        TEST_ASSERT( n->f_int->getType() == kInt );
        TEST_ASSERT( n->f_float->getType() == kFloat );
        TEST_ASSERT( n->f_string->getType() == kString );

        TEST_ASSERT( n->f_int->asInt() == 0 );
        TEST_ASSERT( n->f_float->asFloat() == 0.0f );
        TEST_ASSERT( n->f_string->asString() == "" );

        n->f_int->set(12);
        n->f_float->set(0.5f);
        n->f_string->set("hello");

        TEST_ASSERT( n->f_int->asInt() == 12 );
        TEST_ASSERT( n->f_float->asFloat() == 0.5f );
        TEST_ASSERT( n->f_string->asString() == "hello" );
    }

};