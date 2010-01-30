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

#include "global.h"
#include "handlers.h"
#include "shader loader.h"

int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE /*| GLUT_MULTISAMPLE*/);
	glutInitWindowSize(g.window_width,g.window_height);
	glutInitWindowPosition(800,100);
	glutCreateWindow(g.window_title);

	// glew initialization
	glewInit();

	// OpenGL initialization
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glWindowPos2i(0,0);
	glDisable(GL_MULTISAMPLE);

	// shader initialization
	g.program = load_shaders();
	g.s_index = glGetUniformLocation(g.program,"s");
	g.b_index = glGetUniformLocation(g.program,"b");
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
