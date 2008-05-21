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

#include <string>
#include <iostream>
#include <NodeCore/NodeCore.h>
 
using namespace NodeCore;
using namespace std;

int main(int argc, char* argv[])
{
    NodeLibraryManager *manager = new NodeLibraryManager();
    NodeLibrary *coreVectorLibrary = manager->loadLatest("corevector");
    Node *rectNode = coreVectorLibrary->createNode("RectNode");
    rectNode->set("x", 10.0F);
    rectNode->set("y", 10.0F);
    rectNode->set("width", 100.0F);
    rectNode->set("height", 100.0F);
    Canvas *c = (Canvas *)rectNode->outputAsData();
    c->save("test.pdf");
	cout << "Wrote test.pdf." << endl;
}