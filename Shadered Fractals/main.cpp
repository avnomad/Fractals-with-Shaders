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

	// methods
	Global()
		:directInput(GetModuleHandle(NULL)),
		mouse(directInput)
	{
		window_width = 800;
		window_height = 800;
		fractal_center_x = 0;
		fractal_center_y = 0;
		mouse_z = 9592;	// ln(0.004)/(ln(10)/4000)

		s = exp(wheel_factor*mouse_z);	// 0.004
		b[0] = fractal_center_x - 0.5f*s*window_width;
		b[1] = fractal_center_y - 0.5f*s*window_height;

	} // end Global default constructor

} g; // end struct Global

const char *const Global::window_title = "drawing fractals using shaders";
const float Global::wheel_factor = -0.000575646f;	// ln(10)/4000
					// 120 is the smallest change in mouse_z



void display()
{
	//glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1,0,0);
	glRecti(-1,-1,1,1);

	glutSwapBuffers();
} // end function display


void idle()
{
	bool change = false;

	g.mouse.getState();
	if(g.mouse.Z != 0)
	{
		g.mouse_z += g.mouse.Z;
		g.s = exp(g.wheel_factor*g.mouse_z);
		glUniform1f(g.s_index,g.s);

		change = true;
	} // end if

	if(g.mouse.button[0] & 0x80)
	{
		if(g.mouse.X != 0)
		{
			g.fractal_center_x -= g.s*g.mouse.X;
			change = true;
		} // end if

		if(g.mouse.Y != 0)
		{
			g.fractal_center_y += g.s*g.mouse.Y;
			change = true;
		} // end if
	} // end if

	if(change)
	{
		g.b[0] = g.fractal_center_x - 0.5f*g.s*g.window_width;
		g.b[1] = g.fractal_center_y - 0.5f*g.s*g.window_height;
		glUniform2fv(g.b_index,1,g.b);

		system("CLS");
		cout << "fractal center x:\t" << g.fractal_center_x << '\n';
		cout << "fractal center y:\t" << g.fractal_center_y << '\n';
		cout << "s zoom factor:\t\t" << g.s << '\n';

		glutPostRedisplay();
	} // end if
} // end function active_motion


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:	// escape key
		exit(0);
	} // end switch
} // end function keyboard


void reshape(int w, int h)
{
	g.window_width = w;
	g.window_height = h;

	g.b[0] = g.fractal_center_x - 0.5f*g.s*g.window_width;
	g.b[1] = g.fractal_center_y - 0.5f*g.s*g.window_height;
	glUniform2fv(g.b_index,1,g.b);

	glViewport(0,0,(GLsizei)w,(GLsizei)h);
} // end function reshape


void first_reshape(int w, int h)
{
	reshape(w,h);
	g.mouse.setCooperativeLevel(FindWindow(0,g.window_title),DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	g.mouse.acquire();
	glutReshapeFunc(reshape);
} // end function first_reshape


int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(g.window_width,g.window_height);
	glutInitWindowPosition(800,100);
	glutCreateWindow(g.window_title);

	// glew initialization
	glewInit();

	// OpenGL initialization
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glWindowPos2i(0,0);

	// shader initialization
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

	g.s_index = glGetUniformLocation(program,"s");
	g.b_index = glGetUniformLocation(program,"b");

	glUniform1f(g.s_index,g.s);
	glUniform2fv(g.b_index,1,g.b);

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(first_reshape);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
} // end function main
