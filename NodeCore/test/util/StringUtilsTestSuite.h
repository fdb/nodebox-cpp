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

#include <NodeCore/stringutils.h>

using namespace NodeCore;

class StringUtilsTestSuite : public Test::Suite
{
public:
	StringUtilsTestSuite()
	{
		TEST_ADD(StringUtilsTestSuite::test_to_lower);
		TEST_ADD(StringUtilsTestSuite::test_to_upper);
	}

private:
    void test_to_lower()
    {
        TEST_ASSERT( string_to_lower("") == "" );
        TEST_ASSERT( string_to_lower("1a2b3c") == "1a2b3c" );
        TEST_ASSERT( string_to_lower("1A2B3C") == "1a2b3c" );
    }

    void test_to_upper()
    {
        TEST_ASSERT( string_to_upper("") == "" );
        TEST_ASSERT( string_to_upper("1A2B3C") == "1A2B3C" );
        TEST_ASSERT( string_to_upper("1a2b3c") == "1A2B3C" );
    }

};