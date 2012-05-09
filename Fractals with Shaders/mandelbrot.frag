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

//#pragma optimize(off)
//#pragma debug(on)


#define MAXITER 255
#define THRESHOLD 25.0

uniform float s;
uniform vec2 b;
uniform vec3 color_table[MAXITER+1];
uniform int mandelbrot;
uniform vec2 zulia;

void main()
{
	vec2 z;
	vec2 c;

	if(mandelbrot == 1)
	{
		z = vec2(0,0);
		c = s*gl_FragCoord.xy + b;
	}
	else
	{
		z = s*gl_FragCoord.xy + b;
		c = zulia;
	} // end else
	
	int i;
	for(i = 0 ; i < MAXITER ; ++i)
	{
		z = vec2(z.x*z.x-z.y*z.y,2.0*z.x*z.y)+c;
		if (dot(z,z)>THRESHOLD)
			break;
	} // end for

	/*if(gl_FragCoord.x < 400)
		if(gl_FragCoord.y < 400)
			gl_FragColor = vec4(color_table[0],1.0);
		else
			gl_FragColor = vec4(color_table[50],1.0);
	else
		if(gl_FragCoord.y < 400)
			gl_FragColor = vec4(color_table[100],1.0);
		else
			gl_FragColor = vec4(color_table[150],1.0);*/
	gl_FragColor = vec4(color_table[i],1.0);
	

	if(mandelbrot == 0)
	{
		z = s*gl_FragCoord.xy + b;
		if(length(z)< 0.005)
			gl_FragColor = gl_Color;
		if(length(z-zulia) < 0.005)
			gl_FragColor = 1.0-gl_Color;
		else if(length(z-zulia) < 0.010)
			gl_FragColor = gl_Color;
	} // end else
}
