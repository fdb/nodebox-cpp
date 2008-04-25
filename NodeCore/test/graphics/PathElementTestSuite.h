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

class PathElementTestSuite : public Test::Suite
{
public:
    PathElementTestSuite()
    {
        TEST_ADD(PathElementTestSuite::test_init_errors);
        TEST_ADD(PathElementTestSuite::test_accessors);
    }

private:
    void test_init_errors()
    {
        TEST_THROWS_NOTHING( new PathElement(kClose) );
        TEST_THROWS( new PathElement(kClose, 1, 2), NodeBoxError );
        TEST_THROWS( new PathElement(kClose, 1, 2, 3, 4, 5, 6), NodeBoxError );
        
        TEST_THROWS_NOTHING( new PathElement(kMoveto, 1, 2) );
        TEST_THROWS( new PathElement(kMoveto), NodeBoxError );
        TEST_THROWS( new PathElement(kMoveto, 1, 2, 3, 4, 5, 6), NodeBoxError );

        TEST_THROWS_NOTHING( new PathElement(kLineto, 1, 2) );
        TEST_THROWS( new PathElement(kLineto), NodeBoxError );
        TEST_THROWS( new PathElement(kLineto, 1, 2, 3, 4, 5, 6), NodeBoxError );

        TEST_THROWS_NOTHING( new PathElement(kCurveto, 1, 2, 3, 4, 5, 6) );
        TEST_THROWS( new PathElement(kCurveto), NodeBoxError );
        TEST_THROWS( new PathElement(kCurveto, 1, 2), NodeBoxError );
    }

    void test_accessors()
    {
        PathElement *p1 = new PathElement();
        TEST_ASSERT( p1->getCmd() == kClose );
        TEST_ASSERT( p1->getPoint() == NodeCore::Point(0, 0) );
        TEST_ASSERT( p1->getCtrl1() == NodeCore::Point(0, 0) );
        TEST_ASSERT( p1->getCtrl2() == NodeCore::Point(0, 0) );

        PathElement *p2 = new PathElement(kMoveto, 1, 2);
        TEST_ASSERT( p2->getCmd() == kMoveto );
        TEST_ASSERT( p2->getPoint() == NodeCore::Point(1, 2) );
        TEST_ASSERT( p2->getCtrl1() == NodeCore::Point(0, 0) );
        TEST_ASSERT( p2->getCtrl2() == NodeCore::Point(0, 0) );

        PathElement *p3 = new PathElement(kLineto, 1, 2);
        TEST_ASSERT( p3->getCmd() == kLineto );
        TEST_ASSERT( p3->getPoint() == NodeCore::Point(1, 2) );
        TEST_ASSERT( p3->getCtrl1() == NodeCore::Point(0, 0) );
        TEST_ASSERT( p3->getCtrl2() == NodeCore::Point(0, 0) );

        PathElement *p4 = new PathElement(kCurveto, 1, 2, 3, 4, 5, 6);
        TEST_ASSERT( p4->getCmd() == kCurveto );
        TEST_ASSERT( p4->getPoint() == NodeCore::Point(1, 2) );
        TEST_ASSERT( p4->getCtrl1() == NodeCore::Point(3, 4) );
        TEST_ASSERT( p4->getCtrl2() == NodeCore::Point(5, 6) );
    }

};