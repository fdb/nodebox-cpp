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

class RectTestSuite : public Test::Suite
{
public:
    RectTestSuite()
    {
        TEST_ADD(RectTestSuite::test_empty);
        TEST_ADD(RectTestSuite::test_intersects);
        TEST_ADD(RectTestSuite::test_united);
        TEST_ADD(RectTestSuite::test_contains);
    }

private:

    void test_empty()
    {
        TEST_ASSERT( ! NodeCore::Rect(100, 100, 100, 100).isEmpty() );
        TEST_ASSERT( ! NodeCore::Rect(1, 1, 1, 1).isEmpty() );
        TEST_ASSERT( ! NodeCore::Rect(0, 0, 1, 1).isEmpty() );
        TEST_ASSERT( ! NodeCore::Rect(0, 0, -100, -200).isEmpty() );
        TEST_ASSERT( NodeCore::Rect(0, 0, 0, 0).isEmpty() );
        TEST_ASSERT( NodeCore::Rect(-10, 0, 0, 10).isEmpty() );
        TEST_ASSERT( NodeCore::Rect(-10, 0, 200, 0).isEmpty() );
    }
    
    void test_intersects()
    {
        TEST_ASSERT( ! NodeCore::Rect(0, 0, 20, 20).intersects(NodeCore::Rect(100, 100, 20, 20)) );
        TEST_ASSERT( NodeCore::Rect(0, 0, 20, 20).intersects(NodeCore::Rect(0, 0, 20, 20)) );    
    }
    
    void test_united() {
        NodeCore::Rect r1 = NodeCore::Rect(10, 20, 30, 40);
        NodeCore::Rect r2 = NodeCore::Rect(40, 10, 50, 30);
        TEST_ASSERT( r1.united(r2) == NodeCore::Rect(10, 10, 80, 50) );
    }
    
    void test_contains() {
        NodeCore::Rect r = NodeCore::Rect(10, 20, 30, 40);
        TEST_ASSERT( r.contains(NodeCore::Point(10, 20)) );
        TEST_ASSERT( r.contains(NodeCore::Point(11, 22)) );
        TEST_ASSERT( r.contains(NodeCore::Point(40, 60)) );
        TEST_ASSERT( ! r.contains(NodeCore::Point(0, 0)) );
        TEST_ASSERT( ! r.contains(NodeCore::Point(-11, -22)) );
        TEST_ASSERT( ! r.contains(NodeCore::Point(100, 200)) );
        TEST_ASSERT( ! r.contains(NodeCore::Point(15, 200)) );
        TEST_ASSERT( ! r.contains(NodeCore::Point(200, 25)) );

        TEST_ASSERT( r.contains(NodeCore::Rect(10, 20, 30, 40)) );
        TEST_ASSERT( r.contains(NodeCore::Rect(15, 25, 5, 5)) );
        TEST_ASSERT( ! r.contains(NodeCore::Rect(15, 25, 30, 40)) );
        TEST_ASSERT( ! r.contains(NodeCore::Rect(1, 2, 3, 4)) );
        TEST_ASSERT( ! r.contains(NodeCore::Rect(15, 25, 300, 400)) );
        TEST_ASSERT( ! r.contains(NodeCore::Rect(15, 25, 5, 400)) );
        TEST_ASSERT( ! r.contains(NodeCore::Rect(15, 25, 400, 5)) );
    }
};