#include <Direct Input/DirectInput Wrapper.h>
#include <Direct Input/Mouse Wrapper.h>

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

		ofstream out(settings_file_name);	// for some reason the program exits prematurely in here...

		if(!out)
		{
			cerr << "failed to save settings." << endl;
			return;
		} // end if

		out << fractal_center_x << '\n';
		out << fractal_center_y << '\n';
		out << mouse_z << '\n';
		out << mandelbrot << '\n';
		out << active_color_table << '\n';
		out << zulia[0] << '\n';
		out << zulia[1] << '\n';
		out << file_number << '\n';

		out.close();
	} // end Global destructor

} g; // end struct Global

const char *const Global::window_title = "drawing fractals using shaders";
const float Global::wheel_factor = -0.000575646f;	// ln(10)/4000
const char *const Global::settings_file_name = "settings.dat";

					// 120 is the smallest change in mouse_z
