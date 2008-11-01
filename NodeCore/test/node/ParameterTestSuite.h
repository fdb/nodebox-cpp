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

#include <NodeCore/NodeCore.h>

using namespace NodeCore;

class ParameterTestSuite : public Test::Suite
{
public:
	ParameterTestSuite()
	{
		TEST_ADD(ParameterTestSuite::test_values);
		TEST_ADD(ParameterTestSuite::test_channels);
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
    
    void test_channels()
    {
        Node *n = new Node();
        Parameter *color = n->addParameter("color", kFloat, 3);
        TEST_ASSERT( color->channelCount() == 3 );
        TEST_THROWS_NOTHING( color->set(0.2f, 0) );
        TEST_THROWS_NOTHING( color->set(0.4f, 1) );
        TEST_THROWS_NOTHING( color->set(0.7f, 2) );
        TEST_THROWS( color->set(0.5f, 3), ValueError );
        TEST_THROWS( color->set(0.5f, -1), ValueError );
    }

};