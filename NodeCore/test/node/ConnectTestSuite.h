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

class NumberGenerator : public Node
{
public:
    NumberGenerator()
    {
        addField("number", kInt);
        addField("out", kInt, kOut);
    }
protected:
    virtual void process()
    {
        int number = asInt("number");
        set("out", number);
    }
    NodeNameMacro(NumberGenerator);
};

class Multiplier : public Node
{
public:
    Multiplier()
    {
        addField("number", kInt);
        addField("multiplier", kInt);
        addField("out", kInt, kOut);
    }
protected:
    virtual void process()
    {
        // Fails for big numbers
        int number = asInt("number");
        int multiplier = asInt("multiplier");
        set("out", number * multiplier);
    }
    NodeNameMacro(Multiplier);
};

class ConnectTestSuite : public Test::Suite
{
public:
	ConnectTestSuite()
	{
		TEST_ADD(ConnectTestSuite::test_dirty);
		TEST_ADD(ConnectTestSuite::test_connect);
		TEST_ADD(ConnectTestSuite::test_cycles);
		TEST_ADD(ConnectTestSuite::test_dirty_propagation);
		TEST_ADD(ConnectTestSuite::test_value_propagation);
		TEST_ADD(ConnectTestSuite::test_disconnect);
	}

private:

    void test_dirty()
    {
        NumberGenerator ng = NumberGenerator();
        TEST_ASSERT( ng.isDirty() );
        ng.update();
        TEST_ASSERT( !ng.isDirty() );
        TEST_ASSERT( ng.asInt("out") == 0 );
        ng.set("number", 12);
        TEST_ASSERT( ng.isDirty() );
        // Asking for the output value doesn't update the node implicitly.
        TEST_ASSERT( ng.asInt("out") == 0 );
        // You have to explicitly update the node to get the new output value.
        ng.update();
        TEST_ASSERT( !ng.isDirty() );
        TEST_ASSERT( ng.asInt("out") == 12 );
    }

    void test_connect()
    {
        NumberGenerator ng = NumberGenerator();
        Multiplier m = Multiplier();
        
        // You need to connect from the downstream node
        TEST_THROWS( ng.getField("out")->connect(&m), ConnectionError );
        
        TEST_ASSERT( !m.getField("number")->isConnected() );
        TEST_ASSERT( !ng.getField("out")->isConnected() );
        TEST_ASSERT( !ng.getField("out")->isConnectedTo(m.getField("number")) );
        TEST_ASSERT( !m.getField("number")->isConnectedTo(ng.getOutputField()) );

        Connection* conn = m.getField("number")->connect(&ng);
        TEST_ASSERT( m.getField("number")->isConnected() );
        TEST_ASSERT( ng.getField("out")->isConnected() );
        TEST_ASSERT( m.getField("number") == conn->getInputField() );
        TEST_ASSERT( &m == conn->getInputNode() );
        TEST_ASSERT( ng.getField("out") == conn->getOutputField() );
        TEST_ASSERT( &ng == conn->getOutputNode() );
        
        TEST_ASSERT( ng.getField("out")->isConnectedTo(m.getField("number")) );
        TEST_ASSERT( m.getField("number")->isConnectedTo(ng.getOutputField()) );
    }

    // Test cyclic connections
    void test_cycles()
    {
        NumberGenerator ng = NumberGenerator();
        // Nodes can't connect to themselves.
        TEST_THROWS( ng.getField("number")->connect(&ng), ConnectionError );
        // TODO: more complex cyclic checks (A -> B -> A)
    }

    // Checks whether changes to one node makes connected nodes dirty.
    void test_dirty_propagation()
    {
        NumberGenerator ng = NumberGenerator();
        Multiplier m = Multiplier();
        // Nodes start out dirty
        TEST_ASSERT( ng.isDirty() );
        TEST_ASSERT( m.isDirty() );
        // Updating makes them clean
        ng.update();
        m.update();
        TEST_ASSERT( !ng.isDirty() );
        TEST_ASSERT( !m.isDirty() );
        // Connecting the multiplier to another node makes it dirty.
        // The output node doesn't become dirty.
        m.getField("number")->connect(&ng);
        TEST_ASSERT( !ng.isDirty() );
        TEST_ASSERT( m.isDirty() );
        m.update();
        TEST_ASSERT( !ng.isDirty() ); // This shouldn't have changed
        TEST_ASSERT( !m.isDirty() );
        // A change to the upstream node should make downstream nodes dirty.
        ng.set("number", 12.0f);
        TEST_ASSERT( ng.isDirty() );
        TEST_ASSERT( m.isDirty() );
        // Updating the downstream node should make all upstreams clean.
        m.update();
        TEST_ASSERT( !ng.isDirty() );
        TEST_ASSERT( !m.isDirty() );
        // Changes to the downstream node don't affect upstreams.
        m.set("multiplier", 1.0f);
        TEST_ASSERT( !ng.isDirty() );
        TEST_ASSERT( m.isDirty() );
    }

    // Checks whether changes to one node propagates the values to downstreams
    void test_value_propagation()
    {
        NumberGenerator ng = NumberGenerator();
        Multiplier m = Multiplier();
        m.set("multiplier", 2);
        m.getField("number")->connect(&ng);
        TEST_ASSERT( m.getOutputField()->asInt() == 0 );
        ng.set("number", 3);
        // Asking for the output value doesn't update the node implicitly.
        TEST_ASSERT( m.isDirty() );
        TEST_ASSERT( m.getOutputField()->asInt() == 0 );
        // Updating the NumberGenerator node has no effect on the Multiplier node.
        ng.update();
        TEST_ASSERT( m.isDirty() );
        TEST_ASSERT( m.getOutputField()->asInt() == 0 );
        m.update();
        TEST_ASSERT( !m.isDirty() );
        TEST_ASSERT( m.getOutputField()->asInt() == 6 );
    }

    void test_disconnect()
    {
        NumberGenerator ng = NumberGenerator();
        Multiplier m = Multiplier();
        m.set("multiplier", 2);
        ng.set("number", 5);
        m.getField("number")->connect(&ng);
        TEST_ASSERT( m.getField("number")->isConnected() );
        TEST_ASSERT( ng.getOutputField()->isConnected() );
        m.update();
        TEST_ASSERT( m.asInt("number") == 5 );
        TEST_ASSERT( m.getOutputField()->asInt() == 10 );

        m.getField("number")->disconnect();
        TEST_ASSERT( !m.getField("number")->isConnected() );
        TEST_ASSERT( !ng.getOutputField()->isConnected() );
        // Number reverts to default after disconnection
        TEST_ASSERT( m.asInt("number") == 0 );
    }
};