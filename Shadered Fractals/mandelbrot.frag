#version 420 compatibility

#define MAXITER 255
#define THRESHOLD 25.0

uniform double s;
uniform dvec2 b;
vec3 color_table[MAXITER+1] = {
	{0.000f,0.000f,0.734f},
	{0.000f,0.300f,0.734f},
	{0.000f,0.734f,0.000f},
	{0.734f,0.734f,0.000f},
	{0.734f,0.000f,0.000f},
	{0.734f,0.000f,0.734f},
	{0.000f,0.734f,0.734f},
	{0.750f,0.750f,0.750f},
	{0.750f,0.859f,0.750f},
	{0.641f,0.781f,0.938f},
	{0.500f,0.000f,0.000f},
	{0.000f,0.500f,0.000f},
	{0.500f,0.500f,0.000f},
	{0.000f,0.000f,0.500f},
	{0.500f,0.000f,0.500f},
	{0.000f,0.500f,0.500f},
	{0.234f,0.359f,0.234f},
	{0.359f,0.359f,0.234f},
	{0.484f,0.359f,0.234f},
	{0.609f,0.359f,0.234f},
	{0.734f,0.359f,0.234f},
	{0.859f,0.359f,0.234f},
	{0.984f,0.359f,0.234f},
	{0.234f,0.484f,0.234f},
	{0.359f,0.484f,0.234f},
	{0.484f,0.484f,0.234f},
	{0.609f,0.484f,0.234f},
	{0.734f,0.484f,0.234f},
	{0.859f,0.484f,0.234f},
	{0.984f,0.484f,0.234f},
	{0.234f,0.609f,0.234f},
	{0.359f,0.609f,0.234f},
	{0.484f,0.609f,0.234f},
	{0.609f,0.609f,0.234f},
	{0.734f,0.609f,0.234f},
	{0.859f,0.609f,0.234f},
	{0.984f,0.609f,0.234f},
	{0.234f,0.734f,0.234f},
	{0.359f,0.734f,0.234f},
	{0.484f,0.734f,0.234f},
	{0.609f,0.734f,0.234f},
	{0.734f,0.734f,0.234f},
	{0.859f,0.734f,0.234f},
	{0.984f,0.734f,0.234f},
	{0.234f,0.859f,0.234f},
	{0.359f,0.859f,0.234f},
	{0.484f,0.859f,0.234f},
	{0.609f,0.859f,0.234f},
	{0.734f,0.859f,0.234f},
	{0.859f,0.859f,0.234f},
	{0.984f,0.859f,0.234f},
	{0.234f,0.984f,0.234f},
	{0.359f,0.984f,0.234f},
	{0.484f,0.984f,0.234f},
	{0.609f,0.984f,0.234f},
	{0.734f,0.984f,0.234f},
	{0.859f,0.984f,0.234f},
	{0.984f,0.984f,0.234f},
	{0.234f,0.234f,0.359f},
	{0.359f,0.234f,0.359f},
	{0.484f,0.234f,0.359f},
	{0.609f,0.234f,0.359f},
	{0.734f,0.234f,0.359f},
	{0.859f,0.234f,0.359f},
	{0.984f,0.234f,0.359f},
	{0.234f,0.359f,0.359f},
	{0.359f,0.359f,0.359f},
	{0.484f,0.359f,0.359f},
	{0.609f,0.359f,0.359f},
	{0.734f,0.359f,0.359f},
	{0.859f,0.359f,0.359f},
	{0.984f,0.359f,0.359f},
	{0.234f,0.484f,0.359f},
	{0.359f,0.484f,0.359f},
	{0.484f,0.484f,0.359f},
	{0.609f,0.484f,0.359f},
	{0.734f,0.484f,0.359f},
	{0.859f,0.484f,0.359f},
	{0.984f,0.484f,0.359f},
	{0.234f,0.609f,0.359f},
	{0.359f,0.609f,0.359f},
	{0.484f,0.609f,0.359f},
	{0.609f,0.609f,0.359f},
	{0.734f,0.609f,0.359f},
	{0.859f,0.609f,0.359f},
	{0.984f,0.609f,0.359f},
	{0.234f,0.734f,0.359f},
	{0.359f,0.734f,0.359f},
	{0.484f,0.734f,0.359f},
	{0.609f,0.734f,0.359f},
	{0.734f,0.734f,0.359f},
	{0.859f,0.734f,0.359f},
	{0.984f,0.734f,0.359f},
	{0.234f,0.859f,0.359f},
	{0.359f,0.859f,0.359f},
	{0.484f,0.859f,0.359f},
	{0.609f,0.859f,0.359f},
	{0.734f,0.859f,0.359f},
	{0.859f,0.859f,0.359f},
	{0.984f,0.859f,0.359f},
	{0.234f,0.984f,0.359f},
	{0.359f,0.984f,0.359f},
	{0.484f,0.984f,0.359f},
	{0.609f,0.984f,0.359f},
	{0.734f,0.984f,0.359f},
	{0.859f,0.984f,0.359f},
	{0.984f,0.984f,0.359f},
	{0.234f,0.234f,0.484f},
	{0.359f,0.234f,0.484f},
	{0.484f,0.234f,0.484f},
	{0.609f,0.234f,0.484f},
	{0.734f,0.234f,0.484f},
	{0.859f,0.234f,0.484f},
	{0.984f,0.234f,0.484f},
	{0.234f,0.359f,0.484f},
	{0.359f,0.359f,0.484f},
	{0.484f,0.359f,0.484f},
	{0.609f,0.359f,0.484f},
	{0.734f,0.359f,0.484f},
	{0.859f,0.359f,0.484f},
	{0.984f,0.359f,0.484f},
	{0.234f,0.484f,0.484f},
	{0.359f,0.484f,0.484f},
	{0.484f,0.484f,0.484f},
	{0.609f,0.484f,0.484f},
	{0.734f,0.484f,0.484f},
	{0.859f,0.484f,0.484f},
	{0.984f,0.484f,0.484f},
	{0.234f,0.609f,0.484f},
	{0.359f,0.609f,0.484f},
	{0.484f,0.609f,0.484f},
	{0.609f,0.609f,0.484f},
	{0.734f,0.609f,0.484f},
	{0.859f,0.609f,0.484f},
	{0.984f,0.609f,0.484f},
	{0.234f,0.734f,0.484f},
	{0.359f,0.734f,0.484f},
	{0.484f,0.734f,0.484f},
	{0.609f,0.734f,0.484f},
	{0.734f,0.734f,0.484f},
	{0.859f,0.734f,0.484f},
	{0.984f,0.734f,0.484f},
	{0.234f,0.859f,0.484f},
	{0.359f,0.859f,0.484f},
	{0.484f,0.859f,0.484f},
	{0.609f,0.859f,0.484f},
	{0.734f,0.859f,0.484f},
	{0.859f,0.859f,0.484f},
	{0.984f,0.859f,0.484f},
	{0.234f,0.984f,0.484f},
	{0.359f,0.984f,0.484f},
	{0.484f,0.984f,0.484f},
	{0.609f,0.984f,0.484f},
	{0.734f,0.984f,0.484f},
	{0.859f,0.984f,0.484f},
	{0.984f,0.984f,0.484f},
	{0.234f,0.234f,0.609f},
	{0.359f,0.234f,0.609f},
	{0.484f,0.234f,0.609f},
	{0.609f,0.234f,0.609f},
	{0.734f,0.234f,0.609f},
	{0.859f,0.234f,0.609f},
	{0.984f,0.234f,0.609f},
	{0.234f,0.359f,0.609f},
	{0.359f,0.359f,0.609f},
	{0.484f,0.359f,0.609f},
	{0.609f,0.359f,0.609f},
	{0.734f,0.359f,0.609f},
	{0.859f,0.359f,0.609f},
	{0.984f,0.359f,0.609f},
	{0.234f,0.484f,0.609f},
	{0.359f,0.484f,0.609f},
	{0.484f,0.484f,0.609f},
	{0.609f,0.484f,0.609f},
	{0.734f,0.484f,0.609f},
	{0.859f,0.484f,0.609f},
	{0.984f,0.484f,0.609f},
	{0.234f,0.609f,0.609f},
	{0.359f,0.609f,0.609f},
	{0.484f,0.609f,0.609f},
	{0.609f,0.609f,0.609f},
	{0.734f,0.609f,0.609f},
	{0.859f,0.609f,0.609f},
	{0.984f,0.609f,0.609f},
	{0.234f,0.734f,0.609f},
	{0.359f,0.734f,0.609f},
	{0.484f,0.734f,0.609f},
	{0.609f,0.734f,0.609f},
	{0.734f,0.734f,0.609f},
	{0.859f,0.734f,0.609f},
	{0.984f,0.734f,0.609f},
	{0.234f,0.859f,0.609f},
	{0.359f,0.859f,0.609f},
	{0.484f,0.859f,0.609f},
	{0.609f,0.859f,0.609f},
	{0.734f,0.859f,0.609f},
	{0.859f,0.859f,0.609f},
	{0.984f,0.859f,0.609f},
	{0.234f,0.984f,0.609f},
	{0.359f,0.984f,0.609f},
	{0.484f,0.984f,0.609f},
	{0.609f,0.984f,0.609f},
	{0.734f,0.984f,0.609f},
	{0.859f,0.984f,0.609f},
	{0.984f,0.984f,0.609f},
	{0.234f,0.234f,0.734f},
	{0.359f,0.234f,0.734f},
	{0.484f,0.234f,0.734f},
	{0.609f,0.234f,0.734f},
	{0.734f,0.234f,0.734f},
	{0.859f,0.234f,0.734f},
	{0.984f,0.234f,0.734f},
	{0.234f,0.359f,0.734f},
	{0.359f,0.359f,0.734f},
	{0.484f,0.359f,0.734f},
	{0.609f,0.359f,0.734f},
	{0.734f,0.359f,0.734f},
	{0.859f,0.359f,0.734f},
	{0.984f,0.359f,0.734f},
	{0.234f,0.484f,0.734f},
	{0.359f,0.484f,0.734f},
	{0.484f,0.484f,0.734f},
	{0.609f,0.484f,0.734f},
	{0.734f,0.484f,0.734f},
	{0.859f,0.484f,0.734f},
	{0.984f,0.484f,0.734f},
	{0.234f,0.609f,0.734f},
	{0.359f,0.609f,0.734f},
	{0.484f,0.609f,0.734f},
	{0.609f,0.609f,0.734f},
	{0.734f,0.609f,0.734f},
	{0.859f,0.609f,0.734f},
	{0.984f,0.609f,0.734f},
	{0.234f,0.734f,0.734f},
	{0.359f,0.734f,0.734f},
	{0.484f,0.734f,0.734f},
	{0.609f,0.734f,0.734f},
	{0.734f,0.734f,0.734f},
	{0.859f,0.734f,0.734f},
	{0.984f,0.734f,0.734f},
	{0.234f,0.859f,0.734f},
	{0.359f,0.859f,0.734f},
	{0.484f,0.859f,0.734f},
	{0.609f,0.859f,0.734f},
	{0.734f,0.859f,0.734f},
	{0.859f,0.859f,0.734f},
	{0.984f,0.969f,0.938f},
	{0.625f,0.625f,0.641f},
	{0.500f,0.500f,0.500f},
	{0.984f,0.000f,0.000f},
	{0.000f,0.984f,0.000f},
	{0.984f,0.984f,0.000f},
	{0.000f,0.000f,0.984f},
	{0.984f,0.000f,0.984f},
	{0.000f,0.984f,0.984f},
	{0.000f,0.000f,0.000f}
};

uniform int mandelbrot;
uniform vec2 zulia;

void main()
{
	dvec2 z;
	dvec2 c;

	if(mandelbrot == 1)
	{
		z = dvec2(0,0);
		c = s*dvec2(gl_FragCoord.xy) + b;
	}
	else
	{
		z = s*gl_FragCoord.xy + b;
		c = zulia;
	} // end else
	
	int i;
	for(i = 0 ; i < MAXITER ; ++i)
	{
		z = dvec2(z.x*z.x-z.y*z.y,2.0*z.x*z.y)+c;
		if (dot(z,z)>THRESHOLD)
			break;
	} // end for
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
