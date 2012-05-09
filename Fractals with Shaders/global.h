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

#include <Direct Input/DirectInput Wrapper.h>
#include <Direct Input/Mouse Wrapper.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
using std::ifstream;
using std::ofstream;

/* just grouping all the global variables in a global object g. */
struct Global
{
	// fields
	DirectInput directInput;
	DIMouse mouse;

	int window_width;
	int window_height;
	static const char *const window_title;

	int mouse_z;
	static const float wheel_factor;	// ln(10)/4000
	float fractal_center_x;
	float fractal_center_y;

	// uniforms
	float s;
	GLint s_index;
	float b[2];
	GLint b_index;
	GLint color_table_index;
	int mandelbrot;
	GLint mandelbrot_index;
	float zulia[2];
	GLint zulia_index;

	GLuint program;

	unsigned int active_color_table;
	unsigned int file_number;
	bool delete_settings;
	static const char *const settings_file_name;

	// methods
	Global()
		:directInput(GetModuleHandle(NULL)),
		mouse(directInput)
	{
		ifstream in(settings_file_name);

		if(in)
		{
			in >> fractal_center_x;
			in >> fractal_center_y;
			in >> mouse_z;
			in >> mandelbrot;
			in >> active_color_table;
			in >> zulia[0];
			in >> zulia[1];
			in >> file_number;

			in.close();
		}
		else
		{
			fractal_center_x = -0.6f;
			fractal_center_y = 0;
			mouse_z = 9592;	// ln(0.004)/(ln(10)/4000)
			mandelbrot = 1;
			active_color_table = 0;
			zulia[0] = 0.0f;
			zulia[1] = 0.0f;
			file_number = 0;
		} // end else
		window_width = 800;
		window_height = 800;
		delete_settings = false;

		s = exp(wheel_factor*mouse_z);	// 0.004
		b[0] = fractal_center_x - 0.5f*s*window_width;
		b[1] = fractal_center_y - 0.5f*s*window_height;
	} // end Global default constructor

	~Global()
	{
		if(delete_settings)
		{
			remove(settings_file_name);
			return;
		} // end if

		//ofstream out(settings_file_name);

		//if(!out)
		//{
		//	cerr << "failed to save settings." << endl;
		//	return;
		//} // end if

		//out << fractal_center_x << '\n';
		//out << fractal_center_y << '\n';
		//out << mouse_z << '\n';
		//out << mandelbrot << '\n';
		//out << active_color_table << '\n';
		//out << zulia[0] << '\n';
		//out << zulia[1] << '\n';
		//out << file_number << '\n';

		//out.close();

		/* 
			it appears that when the 'x' button is pressed on a window, glut deletes a critical section
			required by the ofstream constructor before ~Global destructor is called. Thus when an attempt is
			made to construct the 'out' object, function EnterCriticalSection is called on a deleted critical
			section. That would normally result in an exception, but not in a destructor. In that way the
			program closes silently, but the settings are not saved.
			The good news are that stdio calls to fopen and fprintf seem to work, so this is an acceptable
			workarround for now.
	   */

		FILE *out;
		out = fopen(settings_file_name,"w");
		fprintf(out,"%f\n%f\n%d\n%d\n%u\n%f\n%f\n%u\n",fractal_center_x,fractal_center_y,
			mouse_z,mandelbrot,active_color_table,zulia[0],zulia[1],file_number);

		fclose(out);
	} // end Global destructor

} g; // end struct Global

const char *const Global::window_title = "drawing fractals using shaders";
const float Global::wheel_factor = -0.000575646f;	// ln(10)/4000
const char *const Global::settings_file_name = "settings.dat";

					// 120 is the smallest change in mouse_z
