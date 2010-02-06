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

		/*system("CLS");
		cout << "fractal center x:\t" << g.fractal_center_x << '\n';
		cout << "fractal center y:\t" << g.fractal_center_y << '\n';
		cout << "s zoom factor:\t\t" << g.s << '\n';*/

		glutPostRedisplay();
	} // end if

	if(g.mouse.button[1])
	{
		if(g.mouse.X != 0)
			g.zulia[0] += 0.2*g.s*g.mouse.X;
		if(g.mouse.Y != 0)
			g.zulia[1] -= 0.2*g.s*g.mouse.Y;
		glUniform2fv(g.zulia_index,1,g.zulia);
		if(!change) glutPostRedisplay();
	} // end if
} // end function active_motion


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:	// escape key
		exit(0);
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
		g.active_color_table = key-'1';
		glUniform3fv(g.color_table_index,TABLE_ENTRIES,(GLfloat*)color_table[g.active_color_table]);
		break;
	case 'm':
		g.mandelbrot = 1;
		glUniform1i(g.mandelbrot_index,g.mandelbrot);
		break;
	case 'z':
		g.mandelbrot = 0;
		glUniform1i(g.mandelbrot_index,g.mandelbrot);
		break;
	} // end switch
	glutPostRedisplay();
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
