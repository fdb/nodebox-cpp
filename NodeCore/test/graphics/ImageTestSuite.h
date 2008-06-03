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

class ImageTestSuite : public Test::Suite
{
public:
	ImageTestSuite()
	{
		TEST_ADD(ImageTestSuite::test_bounds);
	}

private:
    void test_bounds()
    {
        Image i = Image("testimage.png", 17, 29);
        TEST_ASSERT( i.bounds() == NodeCore::Rect(17, 29, 47, 67) );
        // TODO: enable the following test once width/height are implemented.
        //Image i2 = Image("testimage.png", 17, 29);
        // i2.setWidth(470);
        // TEST_ASSERT( i2.bounds() == NodeCore::Rect(17, 29, 470, 670) );
    }    
};