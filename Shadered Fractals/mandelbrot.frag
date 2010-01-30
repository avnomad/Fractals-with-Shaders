uniform float s;
uniform vec2 b;

#define MAXITER 255
#define THRESHOLD 25


void main()
{
	vec2 z = vec2(0,0);
	vec2 c = s*gl_FragCoord.xy + b;
	
	int i;
	for(i = 0 ; i < MAXITER ; ++i)
	{
		z = vec2(z.x*z.x-z.y*z.y,2.0*z.x*z.y)+c;
		if (dot(z,z)>THRESHOLD)
			break;
	}
	float factor = float(i)/MAXITER;

	gl_FragColor = vec4(factor,factor,0.5,1.0);
	
	if(length(c)<0.005) gl_FragColor = vec4(1,0,0,1);
}
