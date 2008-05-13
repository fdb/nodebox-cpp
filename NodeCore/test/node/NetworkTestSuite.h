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
#include "TestNodes.h"

using namespace NodeCore;

class NetworkTestSuite : public Test::Suite
{
public:
	NetworkTestSuite()
	{
		TEST_ADD(NetworkTestSuite::test_naming);
		TEST_ADD(NetworkTestSuite::test_rename);
		TEST_ADD(NetworkTestSuite::test_container);
		TEST_ADD(NetworkTestSuite::test_dirty);
		TEST_ADD(NetworkTestSuite::test_rendered_node);
		TEST_ADD(NetworkTestSuite::test_processing);
	}

private:
    void test_naming()
    {
        Network* net = new Network();
        TEST_ASSERT( net->defaultName() == "Network" );
        TEST_ASSERT( net->className() == "Network" );
        TEST_ASSERT( net->getName() == "Network" );
    }
    
    void test_rename()
    {
        Network* net = new Network();
        Node* n1 = new Node(kInt);
        n1->setName("node1");
        net->add(n1);
        TEST_ASSERT( net->rename(n1, "node1") );
        TEST_ASSERT( n1->getName() == "node1" );
        TEST_ASSERT( net->rename(n1, "node768") );
        TEST_ASSERT( n1->getName() == "node768" );
        TEST_ASSERT( net->contains("node768") );
        TEST_ASSERT( !net->contains("node1") );
        Node* n2 = new Node(kInt);
        n2->setName("node2");
        net->add(n2);
        TEST_ASSERT( net->rename(n1, "node1") );
        TEST_ASSERT( !net->rename(n1, "node2") );
        TEST_ASSERT( n1->getName() == "node1" );
        // Setting the name from a node also calls rename on the network
        n2->setName("node1");
        TEST_ASSERT( n2->getName() == "node2" );
    }
    
    void test_container()
    {
        Network* net = new Network();
        Node* n1 = new Node(kInt);
        n1->setName("node1");
        Node* n2 = new Node(kInt);
        n2->setName("node2");
        TEST_ASSERT( net->isEmpty() );
        TEST_ASSERT( net->size() == 0 );
        TEST_ASSERT( net->add(n1) );
        TEST_ASSERT( net->add(n2) );
        TEST_ASSERT( !net->isEmpty() );
        TEST_ASSERT( net->size() == 2 );
        TEST_ASSERT( n1->getNetwork() == net );
        TEST_ASSERT( n2->getNetwork() == net );
        TEST_ASSERT( net->getNode("node1") == n1 );
        TEST_ASSERT( net->getNode("node2") == n2 );        
        TEST_ASSERT( !net->add(n1) ); // Try adding an already added node.
        TEST_ASSERT( net->size() == 2 );
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
        Node* n1 = new Node(kInt);
        n1->setName("node1");
        Node* n2 = new Node(kInt);
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
    
    void test_rendered_node()
    {
        Network* net = new Network();
        Node* n1 = new Node(kInt);
        n1->setName("node1");
        TEST_THROWS( net->update(), NodeProcessingError ); // No node to render
        TEST_THROWS( net->setRenderedNode(n1), NodeNotInNetwork );
        n1->setNetwork(net);
        TEST_THROWS_NOTHING( net->setRenderedNode(n1) );
        TEST_THROWS_NOTHING( net->update() );
        net->remove(n1);
        TEST_ASSERT( net->getRenderedNode() == NULL );
        TEST_THROWS( net->update(), NodeProcessingError ); // No node to render
        TEST_THROWS( net->setRenderedNode(n1), NodeNotInNetwork );
    }
    
    void test_processing()
    {
        Network* net = new Network();
        NumberGenerator *ng = new NumberGenerator();
        Multiplier *m = new Multiplier();
        NumberGenerator *ng2 = new NumberGenerator(); // A node out of the connected stream
        ng2->setName("ng2");
        net->add(ng);
        net->add(m);
        net->add(ng2);
        ng->set("number", 5);
        m->getField("number")->connect(ng);
        m->set("multiplier", 3);
        TEST_ASSERT( net->isDirty() );
        TEST_THROWS( net->update(), NodeProcessingError ); // No node to render
        net->setRenderedNode(m);
        net->update();
        TEST_ASSERT( m->outputAsInt() == 15 );
        TEST_ASSERT( net->outputAsInt() == 15 );
        TEST_ASSERT( !net->isDirty() );
        ng2->set("number", 88);
        // Because we changed a node in the network that is not connected to the 
        // rendered node, the network does not become dirty.
        TEST_ASSERT( !net->isDirty() );
        ng->set("number", 11);
        net->update();
        TEST_ASSERT( m->outputAsInt() == 33 );
        TEST_ASSERT( net->outputAsInt() == 33 );
    }

};