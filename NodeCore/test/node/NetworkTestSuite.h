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

class NetworkTestSuite : public Test::Suite
{
public:
	NetworkTestSuite()
	{
		TEST_ADD(NetworkTestSuite::test_naming);
		TEST_ADD(NetworkTestSuite::test_container);
		TEST_ADD(NetworkTestSuite::test_dirty);
	}

private:
    void test_naming()
    {
        Network* net = new Network();
        TEST_ASSERT( net->defaultName() == "Network" );
        TEST_ASSERT( net->className() == "Network" );
        TEST_ASSERT( net->getName() == "Network" );
    }
    
    void test_container()
    {
        Network* net = new Network();
        Node* n1 = new Node();
        n1->setName("node1");
        Node* n2 = new Node();
        n2->setName("node2");
        TEST_ASSERT( net->isEmpty() );
        TEST_ASSERT( net->size() == 0 );
        net->add(n1);
        net->add(n2);
        TEST_ASSERT( !net->isEmpty() );
        TEST_ASSERT( net->size() == 2 );
        TEST_ASSERT( n1->getNetwork() == net );
        TEST_ASSERT( n2->getNetwork() == net );
        TEST_ASSERT( net->getNode("node1") == n1 );
        TEST_ASSERT( net->getNode("node2") == n2 );
        net->remove(n1);
        TEST_ASSERT( n1->getNetwork() == NULL );
        TEST_ASSERT( net->size() == 1 );
        TEST_ASSERT( net->getNode("node1") == NULL );
        TEST_ASSERT( net->getNode("nonexistantnode") == NULL );
    }
    
    void test_dirty()
    {
        Network* net = new Network();
        TEST_ASSERT( net->isDirty() );
        TEST_THROWS( net->update(), NodeProcessingError ); // No node to render
        Node* n1 = new Node();
        n1->setName("node1");
        Node* n2 = new Node();
        n2->setName("node2");
        net->add(n1);
        net->add(n2);
        TEST_THROWS( net->update(), NodeProcessingError ); // Not set as rendered node
        net->setRenderedNode(n1);
        TEST_ASSERT( net->isDirty() );
        TEST_ASSERT( n1->isDirty() );
        TEST_ASSERT( n2->isDirty() );
        TEST_THROWS_NOTHING( net->update() );
        TEST_ASSERT( !net->isDirty() );
        TEST_ASSERT( !n1->isDirty() );
        TEST_ASSERT( n2->isDirty() ); // n2 was not updated
    }

};