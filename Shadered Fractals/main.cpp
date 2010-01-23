#include <gl/glew.h>
#include <gl/glut.h>
#include <cstdlib>

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

void display()
{
	//glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0,0,0.5);
	glRecti(-1,-1,1,1);

	glutSwapBuffers();
} // end function display


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:	// escape key
		exit(0);
	} // end switch
} // end function keyboard


void reshape (int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
} // end function reshape


int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(320,320);
	glutInitWindowPosition(800,100);
	glutCreateWindow("drawing fractals using shaders");

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

	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main
