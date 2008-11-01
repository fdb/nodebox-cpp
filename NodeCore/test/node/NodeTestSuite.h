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

class NodeTestSuite : public Test::Suite
{
public:
    NodeTestSuite()
    {
        TEST_ADD(NodeTestSuite::test_naming);
        TEST_ADD(NodeTestSuite::test_parameters);
        TEST_ADD(NodeTestSuite::test_node_naming);
        TEST_ADD(NodeTestSuite::test_parameter_naming);
        TEST_ADD(NodeTestSuite::test_dirty);
    }

private:

    void test_naming()
    {
        Node *n = new Node(kInt);

        TEST_ASSERT( n->defaultName() == "node" );
        TEST_ASSERT( n->className() == "Node" );
        TEST_ASSERT( n->getName() == "node" );
    }

    void test_parameters()
    {
        Node *n = new Node(kInt);
        TEST_THROWS( n->getParameter("f1"), ParameterNotFound );
        Parameter *f1 = n->addParameter("f1", kInt);
        TEST_ASSERT( n->hasParameter("f1") );
        TEST_THROWS_NOTHING( n->getParameter("f1") );
        TEST_ASSERT( n->getParameter("f1") == f1 );
        TEST_THROWS( n->getParameter("x"), ParameterNotFound );
    }

    void test_node_naming()
    {
        Node *n = new Node(kInt);
        // Names can not start with a digit.
        TEST_THROWS( n->setName("1234"), InvalidName );
        // Names can not be in uppercase or contain uppercase letters
        TEST_THROWS( n->setName("UPPERCASE"), InvalidName );
        TEST_THROWS( n->setName("uPpercase"), InvalidName );
        // Names can not have start with underscores
        TEST_THROWS( n->setName("__reserved"), InvalidName );
        // Only lowercase, numbers and underscore are allowed
        TEST_THROWS( n->setName("what!"), InvalidName );
        TEST_THROWS( n->setName("($-_#$34"), InvalidName );
        // Names can not be empty
        TEST_THROWS( n->setName(""), InvalidName );
        // Names can not be longer than 30 characters
        TEST_THROWS( n->setName("very_very_very_very_very_very_long_name"), InvalidName );

        // Some other correct names
        TEST_THROWS_NOTHING( n->setName("radius") );
        TEST_THROWS_NOTHING( n->setName("_test") );
        TEST_THROWS_NOTHING( n->setName("_") );
        TEST_THROWS_NOTHING( n->setName("_1234") );
        TEST_THROWS_NOTHING( n->setName("a1234") );
    }

    void test_parameter_naming()
    {
        Node *n = new Node(kInt);
        // Names can not start with a digit.
        TEST_THROWS( n->addParameter("1234", kInt), InvalidName );
        // Names can not be one of the reserved words.
        TEST_THROWS( n->addParameter("node", kInt), InvalidName );
        TEST_THROWS( n->addParameter("name", kInt), InvalidName );
        // Names can not be in uppercase or contain uppercase letters
        TEST_THROWS( n->addParameter("UPPERCASE", kInt), InvalidName );
        TEST_THROWS( n->addParameter("uPpercase", kInt), InvalidName );
        // Names can not start with double underscores
        TEST_THROWS( n->addParameter("__reserved", kInt), InvalidName );
        // Only lowercase, numbers and underscore are allowed
        TEST_THROWS( n->addParameter("what!", kInt), InvalidName );
        TEST_THROWS( n->addParameter("($-_#$34", kInt), InvalidName );
        // Names can not be empty
        TEST_THROWS( n->addParameter("", kInt), InvalidName );
        // Names can not be longer than 30 characters
        TEST_THROWS( n->addParameter("very_very_very_very_very_very_long_name", kInt), InvalidName );

        // Names can only appear once
        TEST_THROWS_NOTHING( n->addParameter("my_parameter", kInt) );
        TEST_THROWS( n->addParameter("my_parameter", kInt), InvalidName );

        // Some other correct names
        TEST_THROWS_NOTHING( n->addParameter("radius", kInt) );
        TEST_THROWS_NOTHING( n->addParameter("_test", kInt) );
        TEST_THROWS_NOTHING( n->addParameter("_", kInt) );
        TEST_THROWS_NOTHING( n->addParameter("_1234", kInt) );
        TEST_THROWS_NOTHING( n->addParameter("a1234", kInt) );
        TEST_THROWS_NOTHING( n->addParameter("x", kInt) );
        TEST_THROWS_NOTHING( n->addParameter("y", kInt) );
        TEST_THROWS_NOTHING( n->addParameter("dirty", kInt) );
        TEST_THROWS_NOTHING( n->addParameter("process", kInt) );
    }
    
    void test_dirty()
    {
        Node *n = new Node(kInt);
        TEST_ASSERT( n->isDirty() );
        n->update();
        TEST_ASSERT( !n->isDirty() );
        n->addParameter("test", kInt);
        TEST_ASSERT( n->isDirty() );
        n->update();
        TEST_ASSERT( !n->isDirty() );
        n->set("test", 12);
        TEST_ASSERT( n->isDirty() );
        n->update();
        TEST_ASSERT( !n->isDirty() );
        n->getParameter("test")->set(12);
        TEST_ASSERT( n->isDirty() );
        n->update();
        TEST_ASSERT( !n->isDirty() );        
    }

};