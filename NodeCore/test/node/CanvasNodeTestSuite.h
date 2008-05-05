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

#include <iostream>
#include <NodeCore/NodeCore.h>

using namespace std;
using namespace NodeCore;

class RectNode : public CanvasNode {
public:
    RectNode()
    {
        f_x = addField("x", kFloat);
        f_y = addField("y", kFloat);
        f_width = addField("width", kFloat);
        f_height = addField("height", kFloat);
    }

protected:
    virtual void process()
    {
        Canvas c = Canvas();
        BezierPath p = BezierPath();
        p.rect(f_x->asFloat(), f_y->asFloat(), f_width->asFloat(), f_height->asFloat());
        c.append(p);
        setOutput(c);
    }

public:
    Field *f_x;
    Field *f_y;
    Field *f_width;
    Field *f_height;
};

class CanvasNodeTestSuite : public Test::Suite
{
public:
	CanvasNodeTestSuite()
	{
		TEST_ADD(CanvasNodeTestSuite::test_rect_node);
	}

private:
    void test_rect_node()
    {
        RectNode *n = new RectNode();
        TEST_ASSERT( n->f_x->asFloat() == 0 );
        TEST_ASSERT( n->f_y->asFloat() == 0 );
        TEST_ASSERT( n->f_width->asFloat() == 0 );
        TEST_ASSERT( n->f_height->asFloat() == 0 );
        TEST_ASSERT( n->outputAsCanvas() == Canvas() );
        n->set("x", 10.0f);
        n->set("y", 20.0f);
        n->set("width", 30.0f);
        n->set("height", 40.0f);
        n->update();
        Canvas c = n->outputAsCanvas();
        BezierPath r = BezierPath();
        r.rect(10, 20, 30, 40);
        TEST_ASSERT( c.size() == 1 );
        TEST_ASSERT( (*c[0]) == r );
        delete n;
    }
};