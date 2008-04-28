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

class CanvasTestSuite : public Test::Suite
{
public:
	CanvasTestSuite()
	{
		TEST_ADD(CanvasTestSuite::test_size);
		TEST_ADD(CanvasTestSuite::test_copy);
		TEST_ADD(CanvasTestSuite::test_accessors);
		TEST_ADD(CanvasTestSuite::test_equality);
	}

private:

    void test_size()
    {
        Canvas c = Canvas();
        TEST_ASSERT( c.size() == 0 );
        BezierPath p1 = BezierPath();
        c.append(p1);
        TEST_ASSERT( c.size() == 1 );
        BezierPath p2 = BezierPath();
        c.append(p2);
        TEST_ASSERT( c.size() == 2 );
        c.clear();
        TEST_ASSERT( c.size() == 0 );
    }

    void test_copy()
    {
        Canvas c1 = Canvas();    
        BezierPath p1 = BezierPath();
        c1.append(p1);
        TEST_ASSERT( c1.size() == 1 );
        Canvas c2 = Canvas(c1);
        TEST_ASSERT( c2.size() == 1 );
        c1.clear();
        TEST_ASSERT( c1.size() == 0 );
        TEST_ASSERT( c2.size() == 1 );    
    }

    void test_accessors()
    {
        Canvas c = Canvas();    
        BezierPath p0 = BezierPath();
        p0.moveto(1, 2);
        BezierPath p1 = BezierPath();
        p1.moveto(3, 4);
        BezierPath p2 = BezierPath();
        p2.moveto(5, 6);
        c.append(p0);
        c.append(p1);
        c.append(p2);
        TEST_ASSERT( c.size() == 3 );
        TEST_ASSERT( *c[0] == p0 );
        TEST_ASSERT( *c[1] == p1 );
        TEST_ASSERT( *c[2] == p2 );
        TEST_ASSERT( *c[0] != p1 );
        TEST_ASSERT( *c[0] != p2 );
        TEST_ASSERT( *c[1] != p0 );
        TEST_ASSERT( *c[1] != p2 );
        TEST_ASSERT( *c[2] != p0 );
        TEST_ASSERT( *c[2] != p1 );
    }

    void test_equality()
    {
        Canvas c1 = Canvas();
        TEST_ASSERT( c1 == c1 );
        Canvas  c2 = Canvas();
        TEST_ASSERT( c1 == c2 );
        BezierPath p1 = BezierPath();
        BezierPath p2 = BezierPath();
        c1.append(p1);
        c2.append(p2);
        TEST_ASSERT( c1 == c2 );
        Canvas c3 = Canvas();
        TEST_ASSERT( !(c1 == c3) );
    }
};