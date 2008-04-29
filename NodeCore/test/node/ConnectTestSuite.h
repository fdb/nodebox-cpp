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

class IntNode : public Node
{
public:
    IntNode() : m_output(0) {} 
    int getOutput() { return m_output; }
protected:
    void setOutput(int i) { m_output = i; }
    void updateField(Field* f)
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
        NumberGenerator *ng = new NumberGenerator();
        TEST_ASSERT( ng->isDirty() );
        ng->update();
        TEST_ASSERT( !ng->isDirty() );
        TEST_ASSERT( ng->getOutput() == 0 );
        ng->set("number", 12);
        TEST_ASSERT( ng->isDirty() );
        // Asking for the output value doesn't update the node implicitly.
        TEST_ASSERT( ng->getOutput() == 0 );
        // You have to explicitly update the node to get the new output value.
        ng->update();
        TEST_ASSERT( !ng->isDirty() );
        TEST_ASSERT( ng->getOutput() == 12 );
    }

    void test_connect()
    {
        NumberGenerator *ng = new NumberGenerator();
        Multiplier *m = new Multiplier();
        
        TEST_ASSERT( !m->getField("number")->isConnected() );
        TEST_ASSERT( !m->getField("number")->isConnectedTo(ng) );
        TEST_ASSERT( !ng->isOutputConnected() );
        TEST_ASSERT( !ng->isOutputConnectedTo(m) );
        TEST_ASSERT( !ng->isOutputConnectedTo(m->getField("number")) );

        Connection* conn = m->getField("number")->connect(ng);
        TEST_ASSERT( m->getField("number")->isConnected() );
        TEST_ASSERT( m->getField("number")->isConnectedTo(ng) );
        TEST_ASSERT( ng->isOutputConnected() );
        TEST_ASSERT( ng->isOutputConnectedTo(m) );
        TEST_ASSERT( ng->isOutputConnectedTo(m->getField("number")) );
        TEST_ASSERT( m->getField("number") == conn->getInputField() );
        TEST_ASSERT( m == conn->getInputNode() );
        TEST_ASSERT( ng == conn->getOutputNode() );
    }

    // Test cyclic connections
    void test_cycles()
    {
        NumberGenerator *ng = new NumberGenerator();
        // Nodes can't connect to themselves.
        TEST_THROWS( ng->getField("number")->connect(ng), ConnectionError );
        // TODO: more complex cyclic checks (A -> B -> A)
    }

    // Checks whether changes to one node makes connected nodes dirty.
    void test_dirty_propagation()
    {
        NumberGenerator *ng = new NumberGenerator();
        Multiplier *m = new Multiplier();
        // Nodes start out dirty
        TEST_ASSERT( ng->isDirty() );
        TEST_ASSERT( m->isDirty() );
        // Updating makes them clean
        ng->update();
        m->update();
        TEST_ASSERT( !ng->isDirty() );
        TEST_ASSERT( !m->isDirty() );
        // Connecting the multiplier to another node makes it dirty.
        // The output node doesn't become dirty.
        m->getField("number")->connect(ng);
        TEST_ASSERT( !ng->isDirty() );
        TEST_ASSERT( m->isDirty() );
        m->update();
        TEST_ASSERT( !ng->isDirty() ); // This shouldn't have changed
        TEST_ASSERT( !m->isDirty() );
        // A change to the upstream node should make downstream nodes dirty.
        ng->set("number", 12);
        TEST_ASSERT( ng->isDirty() );
        TEST_ASSERT( m->isDirty() );
        // Updating the downstream node should make all upstreams clean.
        m->update();
        TEST_ASSERT( !ng->isDirty() );
        TEST_ASSERT( !m->isDirty() );
        // Changes to the downstream node don't affect upstreams.
        m->set("multiplier", 1);
        TEST_ASSERT( !ng->isDirty() );
        TEST_ASSERT( m->isDirty() );
        // Check if disconnect nodes still propagate.
        m->getField("number")->disconnect();
        m->update();
        ng->update();
        ng->set("number", 12);
        TEST_ASSERT( ng->isDirty() );
        // Disconnected node should not be affected.
        TEST_ASSERT( !m->isDirty() );
    }

    // Checks whether changes to one node propagates the values to downstreams
    void test_value_propagation()
    {
        NumberGenerator *ng = new NumberGenerator();
        Multiplier *m = new Multiplier();
        m->set("multiplier", 2);
        m->getField("number")->connect(ng);
        TEST_ASSERT( m->getOutput() == 0 );
        ng->set("number", 3);
        TEST_ASSERT( m->isDirty() );
        // Asking for the output value doesn't update the node implicitly.
        TEST_ASSERT( m->getOutput() == 0 );
        // Updating the NumberGenerator node has no effect on the Multiplier node.
        ng->update();
        TEST_ASSERT( m->isDirty() );
        TEST_ASSERT( m->getOutput() == 0 );
        m->update();
        TEST_ASSERT( !m->isDirty() );
        TEST_ASSERT( m->getOutput() == 6 );
        // Test if value stops propagating after disconnection.
        m->getField("number")->disconnect();
        TEST_ASSERT( m->isDirty() );
        TEST_ASSERT( !ng->isDirty() );
        ng->set("number", 3);
        m->update();
        TEST_ASSERT( m->getOutput() == 0 );
    }

    void test_disconnect()
    {
        NumberGenerator *ng = new NumberGenerator();
        Multiplier *m = new Multiplier();
        m->set("multiplier", 2);
        ng->set("number", 5);
        m->getField("number")->connect(ng);
        TEST_ASSERT( m->getField("number")->isConnected() );
        TEST_ASSERT( ng->isOutputConnected() );
        m->update();
        TEST_ASSERT( m->asInt("number") == 5 );
        TEST_ASSERT( m->getOutput() == 10 );

        m->getField("number")->disconnect();
        TEST_ASSERT( m->isDirty() );
        TEST_ASSERT( !ng->isDirty() );        
        TEST_ASSERT( !m->getField("number")->isConnected() );
        TEST_ASSERT( !ng->isOutputConnected() );
        // Number reverts to default after disconnection
        m->update();
        TEST_ASSERT( m->getOutput() == 0 );
    }
};