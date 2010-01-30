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
	gl_FragColor = vec4(color_table[i],1.0);
	
	//if(length(c)<0.005) gl_FragColor = gl_Color;
}
