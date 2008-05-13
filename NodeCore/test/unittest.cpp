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

#include "cpptest.h"
#include "graphics/BezierPathTestSuite.h"
#include "graphics/CanvasTestSuite.h"
#include "graphics/PathElementTestSuite.h"
#include "node/ConnectTestSuite.h"
#include "node/FieldTestSuite.h"
#include "node/NetworkTestSuite.h"
#include "node/NodeTestSuite.h"
#include "node/CanvasNodeTestSuite.h"
#include "util/StringUtilsTestSuite.h"

using namespace std;

static void
usage()
{
	cout << "usage: mytest [MODE]\n"
		 << "where MODE may be one of:\n"
		 << "  --compiler\n"
		 << "  --html\n"
		 << "  --text-terse (default)\n"
		 << "  --text-verbose\n";
	exit(0);
}

static auto_ptr<Test::Output>
cmdline(int argc, char* argv[])
{
	if (argc > 2)
		usage(); // will not return
	
	Test::Output* output = 0;
	
	if (argc == 1)
		output = new Test::TextOutput(Test::TextOutput::Verbose);
	else
	{
		const char* arg = argv[1];
		if (strcmp(arg, "--compiler") == 0)
			output = new Test::CompilerOutput;
		else if (strcmp(arg, "--html") == 0)
			output =  new Test::HtmlOutput;
		else if (strcmp(arg, "--text-terse") == 0)
			output = new Test::TextOutput(Test::TextOutput::Terse);
		else if (strcmp(arg, "--text-verbose") == 0)
			output = new Test::TextOutput(Test::TextOutput::Verbose);
		else
		{
			cout << "invalid commandline argument: " << arg << endl;
			usage(); // will not return
		}
	}
	
	return auto_ptr<Test::Output>(output);
}

// Main test program
//
int
main(int argc, char* argv[])
{
	/*
    try
	{
    */
		// Demonstrates the ability to use multiple test suites
		//
		Test::Suite ts;
        // Utility tests
		ts.add(auto_ptr<Test::Suite>(new StringUtilsTestSuite));
        // Graphical tests
		ts.add(auto_ptr<Test::Suite>(new BezierPathTestSuite));
		ts.add(auto_ptr<Test::Suite>(new PathElementTestSuite));
		ts.add(auto_ptr<Test::Suite>(new CanvasTestSuite));
        // Node tests
		ts.add(auto_ptr<Test::Suite>(new NodeTestSuite));
		ts.add(auto_ptr<Test::Suite>(new FieldTestSuite));
		ts.add(auto_ptr<Test::Suite>(new ConnectTestSuite));
		ts.add(auto_ptr<Test::Suite>(new NetworkTestSuite));
		ts.add(auto_ptr<Test::Suite>(new CanvasNodeTestSuite));

		// Run the tests
		//
		auto_ptr<Test::Output> output(cmdline(argc, argv));
		if (ts.run(*output, true))
		{
			Test::HtmlOutput* html = dynamic_cast<Test::HtmlOutput*>(output.get());
			if (html)
				html->generate(cout, true, "MyTest");
		}
	/*
    }
	catch (...)
	{
		cout << "unexpected exception encountered\n";
		return EXIT_FAILURE;
	}
    */
	return EXIT_SUCCESS;
}

