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
        TEST_ADD(NodeTestSuite::test_fields);
        TEST_ADD(NodeTestSuite::test_node_naming);
        TEST_ADD(NodeTestSuite::test_field_naming);
        TEST_ADD(NodeTestSuite::test_naming);
        TEST_ADD(NodeTestSuite::test_dirty);
    }

private:

    void test_naming()
    {
        Node *n = new Node();

        TEST_ASSERT( n->defaultName() == "Node" );
        TEST_ASSERT( n->className() == "Node" );
        TEST_ASSERT( n->getName() == "Node" );
    }

    void test_fields()
    {
        Node *n = new Node();
        TEST_THROWS( n->getField("f1"), FieldNotFound );
        Field *f1 = n->addField("f1", kInt);
        TEST_ASSERT( n->hasField("f1") );
        TEST_THROWS_NOTHING( n->getField("f1") );
        TEST_ASSERT( n->getField("f1") == f1 );
        TEST_THROWS( n->getField("x"), FieldNotFound );
    }

    void test_node_naming()
    {
        Node *n = new Node();
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

    void test_field_naming()
    {
        Node *n = new Node();
        // Names can not start with a digit.
        TEST_THROWS( n->addField("1234", kInt), InvalidName );
        // Names can not be one of the reserved words.
        TEST_THROWS( n->addField("node", kInt), InvalidName );
        TEST_THROWS( n->addField("name", kInt), InvalidName );
        // Names can not be in uppercase or contain uppercase letters
        TEST_THROWS( n->addField("UPPERCASE", kInt), InvalidName );
        TEST_THROWS( n->addField("uPpercase", kInt), InvalidName );
        // Names can not start with double underscores
        TEST_THROWS( n->addField("__reserved", kInt), InvalidName );
        // Only lowercase, numbers and underscore are allowed
        TEST_THROWS( n->addField("what!", kInt), InvalidName );
        TEST_THROWS( n->addField("($-_#$34", kInt), InvalidName );
        // Names can not be empty
        TEST_THROWS( n->addField("", kInt), InvalidName );
        // Names can not be longer than 30 characters
        TEST_THROWS( n->addField("very_very_very_very_very_very_long_name", kInt), InvalidName );

        // Names can only appear once
        TEST_THROWS_NOTHING( n->addField("my_field", kInt) );
        TEST_THROWS( n->addField("my_field", kInt), InvalidName );

        // Some other correct names
        TEST_THROWS_NOTHING( n->addField("radius", kInt) );
        TEST_THROWS_NOTHING( n->addField("_test", kInt) );
        TEST_THROWS_NOTHING( n->addField("_", kInt) );
        TEST_THROWS_NOTHING( n->addField("_1234", kInt) );
        TEST_THROWS_NOTHING( n->addField("a1234", kInt) );
        TEST_THROWS_NOTHING( n->addField("x", kInt) );
        TEST_THROWS_NOTHING( n->addField("y", kInt) );
        TEST_THROWS_NOTHING( n->addField("dirty", kInt) );
        TEST_THROWS_NOTHING( n->addField("process", kInt) );
    }
    
    void test_dirty()
    {
        Node *n = new Node();
        TEST_ASSERT( n->isDirty() );
        n->update();
        TEST_ASSERT( !n->isDirty() );
        n->addField("test", kInt);
        TEST_ASSERT( n->isDirty() );
        n->update();
        TEST_ASSERT( !n->isDirty() );
        n->set("test", 12);
        TEST_ASSERT( n->isDirty() );
        n->update();
        TEST_ASSERT( !n->isDirty() );
        n->getField("test")->set(12);
        TEST_ASSERT( n->isDirty() );
        n->update();
        TEST_ASSERT( !n->isDirty() );        
    }

};