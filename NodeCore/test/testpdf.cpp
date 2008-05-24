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
 
int main(int argc, char* argv[])
{
    Canvas c = Canvas();
    BezierPath p1 = BezierPath();
    p1.rect(0,0,100,100);
    p1.setFillColor(Color::rgbColor(1.0, 0.2, 0.5));
    c.append(p1);
    Image i = Image("nodeboxicon.png", 200, 20);
    c.append(i);
    c.save("test.pdf");
	std::cout << "Wrote test.pdf." << std::endl;
}