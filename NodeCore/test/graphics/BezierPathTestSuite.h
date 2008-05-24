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

class BezierPathTestSuite : public Test::Suite
{
public:
	BezierPathTestSuite()
	{
		TEST_ADD(BezierPathTestSuite::test_size);
		TEST_ADD(BezierPathTestSuite::test_copy);
		TEST_ADD(BezierPathTestSuite::test_copy_pointers);
		TEST_ADD(BezierPathTestSuite::test_accessors);
		TEST_ADD(BezierPathTestSuite::test_equality);
		TEST_ADD(BezierPathTestSuite::test_bounds);
	}

private:
    void test_size()
    {
        BezierPath *p = new BezierPath();
        TEST_ASSERT( p->size() == 0 );
        p->moveto(0, 0);
        TEST_ASSERT( p->size() == 1 );
        p->lineto(100, 100);
        TEST_ASSERT( p->size() == 2 );
        p->clear();
        TEST_ASSERT( p->size() == 0 );
        delete p;
    }
    
    void test_copy()
    {
        BezierPath p1 = BezierPath();
        p1.moveto(0, 0);
        p1.lineto(100, 100);
        TEST_ASSERT( p1.size() == 2 );
        BezierPath p2 = BezierPath(p1);
        TEST_ASSERT( p2.size() == 2 );
        p1.clear();
        TEST_ASSERT( p1.size() == 0 );
        TEST_ASSERT( p2.size() == 2 );
    }
    
    void test_copy_pointers()
    {
        BezierPath *p1 = new BezierPath();
        p1->moveto(0, 0);
        p1->lineto(100, 100);
        TEST_ASSERT( p1->size() == 2 );
        BezierPath *p2 = new BezierPath(*p1);
        TEST_ASSERT( p2->size() == 2 );
        p1->clear();
        TEST_ASSERT( p1->size() == 0 );
        TEST_ASSERT( p2->size() == 2 );
        delete p1, p2;
    }

    void test_accessors()
    {
        BezierPath p1 = BezierPath();
        p1.moveto(1, 2);
        p1.lineto(3, 4);
        p1.close();
        TEST_ASSERT( p1.size() == 3 );
        TEST_ASSERT( p1[0] == PathElement(kMoveto, 1, 2) );
        TEST_ASSERT( p1[1] == PathElement(kLineto, 3, 4) );
        TEST_ASSERT( p1[2] == PathElement(kClose) );
    }

    void test_equality()
    {
        BezierPath p1 = BezierPath();
        TEST_ASSERT( p1 == p1 );
        BezierPath p2 = BezierPath();
        TEST_ASSERT( p1 == p2 );
        BezierPath p3 = BezierPath();
        p3.moveto(1, 2);
        TEST_ASSERT( !(p2 == p3) );
    }

    void test_bounds()
    {
        BezierPath p1 = BezierPath();
        p1.rect(20, 30, 40, 50);
        TEST_ASSERT( p1.bounds() == NodeCore::Rect(20, 30, 40, 50) );
        BezierPath p2 = BezierPath();
        p2.rect(60, 70, 80, 90);
        TEST_ASSERT( p2.bounds() == NodeCore::Rect(60, 70, 80, 90) );
    }
};