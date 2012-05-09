//	Copyright (C) 2010-2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
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

#include "shader loader.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <algorithm>
using std::copy;

#include <string>
using std::string;

#include <iterator>
using std::back_inserter;

#include <char reader.h>



GLuint load_shaders()
{
	ifstream in("mandelbrot.frag");
	string source;
	copy(CharReader(in),CharReader(),back_inserter(source));
	const char *s = source.c_str();

	GLint compile_status,log_length,link_status,validate_status;
	GLuint shader;
	GLuint program;
	cout << std::left << std::setfill('.');

	cout << setw(30) << "Creating shader object";
	if(shader = glCreateShader(GL_FRAGMENT_SHADER))
		cout << "done\n";
	else
		cout << "failed\n";

	cout << setw(30) << "Associating source code";
	glShaderSource(shader,1,&s,NULL);
	cout << "done\n";

	cout << setw(30) << "Compiling shader";
	glCompileShader(shader);
	glGetShaderiv(shader,GL_COMPILE_STATUS,&compile_status);
	glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&log_length);
	s = new char[log_length];
	glGetShaderInfoLog(shader,log_length,NULL,(char*)s);
	if(compile_status == GL_TRUE)
		cout << "done\n";
	else
		cout << "failed\n";
	cout << '\n' << s << '\n';
	delete[] s;

	cout << setw(30) << "Creating shader program";
	if(program = glCreateProgram())
		cout << "done\n";
	else
		cout << "failed\n";

	cout << setw(30) << "Attaching shader object";
	glAttachShader(program,shader);
	cout << "done\n";

	cout << setw(30) << "Linking shader program";
	glLinkProgram(program);
	glGetProgramiv(program,GL_LINK_STATUS,&link_status);
	glGetProgramiv(program,GL_INFO_LOG_LENGTH,&log_length);
	s = new char[log_length];
	glGetProgramInfoLog(program,log_length,NULL,(char*)s);
	if(link_status == GL_TRUE)
		cout << "done\n";
	else
		cout << "failed\n";
	cout << '\n' << s << '\n';
	delete[] s;

	cout << setw(30) << "Validating shader program";
	glValidateProgram(program);
	glGetProgramiv(program,GL_VALIDATE_STATUS,&validate_status);
	glGetProgramiv(program,GL_INFO_LOG_LENGTH,&log_length);
	s = new char[log_length];
	glGetProgramInfoLog(program,log_length,NULL,(char*)s);
	if(validate_status == GL_TRUE)
		cout << "done\n";
	else
		cout << "failed\n";
	cout << '\n' << s << '\n';
	delete[] s;

	cout << setw(30) << "Activating shader program";
	glUseProgram(program);
	cout << "done\n";

	return program;
} // end function load_shaders