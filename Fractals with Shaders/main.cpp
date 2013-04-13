//	Copyright (C) 2010-2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Fractals with Shaders.
 *
 *	Fractals with Shaders is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Fractals with Shaders is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Fractals with Shaders.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gl/glew.h>
#include <gl/glut.h>
#include <cstdlib>
#include <cmath>

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <algorithm>
using std::copy;

#include <iterator>
using std::istream_iterator;
using std::ostream_iterator;

#include <fstream>
using std::ifstream;

#include <ios>
using std::noskipws;

#include "color tables.h"
#include "global.h"
#include "handlers.h"
#include "shader loader.h"

int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE /*| GLUT_MULTISAMPLE*/);
	glutInitWindowSize(g.window_width,g.window_height);
	glutInitWindowPosition(450,130);
	glutCreateWindow(g.window_title);

	// glew initialization
	glewInit();

	// OpenGL initialization
	glPixelStorei(GL_PACK_ALIGNMENT,1);
	glReadBuffer(GL_FRONT);
	glDisable(GL_MULTISAMPLE);

	// color table initialization
	populate_color_tables();

	// shader initialization
	g.program = load_shaders();
	g.s_index = glGetUniformLocation(g.program,"s");
	g.b_index = glGetUniformLocation(g.program,"b");
	g.color_table_index = glGetUniformLocation(g.program,"color_table");
	g.mandelbrot_index = glGetUniformLocation(g.program,"mandelbrot");
	g.zulia_index = glGetUniformLocation(g.program,"zulia");
	glUniform1d(g.s_index,g.s);
	glUniform2dv(g.b_index,1,g.b);
	glUniform3fv(g.color_table_index,TABLE_ENTRIES,(GLfloat*)color_table[g.active_color_table]);
	glUniform1i(g.mandelbrot_index,g.mandelbrot);
	glUniform2dv(g.zulia_index,1,g.zulia);

	// help initialization
	cout << "\n\n";
	const char usageFilePath[] = "../usage.txt";
	ifstream in(usageFilePath);
	if(in)
	{
		in >> noskipws;
		copy(istream_iterator<char>(in),istream_iterator<char>(),ostream_iterator<char>(cout));
	}
	else
		cerr << "Could not read help from file " << usageFilePath << endl;

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(first_reshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
} // end function main
