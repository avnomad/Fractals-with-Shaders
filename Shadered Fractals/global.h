#include <Direct Input/DirectInput Wrapper.h>
#include <Direct Input/Mouse Wrapper.h>

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
	static const float wheel_factor;	// ln(10)/10
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

	// methods
	Global()
		:directInput(GetModuleHandle(NULL)),
		mouse(directInput)
	{
		window_width = 800;
		window_height = 800;
		fractal_center_x = -0.6;
		fractal_center_y = 0;
		mouse_z = 9592;	// ln(0.004)/(ln(10)/4000)
		mandelbrot = 0;
		zulia[0] = 0.0f;
		zulia[1] = 0.0f;

		s = exp(wheel_factor*mouse_z);	// 0.004
		b[0] = fractal_center_x - 0.5f*s*window_width;
		b[1] = fractal_center_y - 0.5f*s*window_height;
	} // end Global default constructor

} g; // end struct Global

const char *const Global::window_title = "drawing fractals using shaders";
const float Global::wheel_factor = -0.000575646f;	// ln(10)/4000
					// 120 is the smallest change in mouse_z
