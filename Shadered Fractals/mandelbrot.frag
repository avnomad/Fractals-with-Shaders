// simple fragment shader

// 'time' contains seconds since the program was linked.
uniform float time;

#define width 1000
#define height 800
#define MAXITER 255
#define THRESHOLD 25
#define MAX_X 0.8
#define MIN_X -2.2
#define MAX_Y 1.2
#define MIN_Y -1.2

void main()
{
	float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;
	mat2 m = mat2(0.005);
	
	//vec2 point = vec2(x*((MAX_X-MIN_X)/width)+MIN_X,y*((MAX_Y-MIN_Y)/height)+MIN_Y);
	//vec2 z = vec2(0,0);
	vec2 z = vec2(x*((MAX_X-MIN_X)/width)+MIN_X,y*((MAX_Y-MIN_Y)/height)+MIN_Y);
	vec2 point = vec2(0.4,-0.15);

	//point = m*point;
	//point += vec2(-1.60,0.0);
	
	int c;
	for(c = 0 ; c < MAXITER ; ++c)
	{
		z = vec2(z.x*z.x-z.y*z.y,2.0*z.x*z.y)+point;
		if (z.x*z.x+z.y*z.y>THRESHOLD)
			break;
	}
	float factor = float(c)/MAXITER;

	gl_FragColor = vec4(factor,factor,0.5,1.0);

	/*if(mod(floor(x/10),2)==0 ^^ mod(floor(y/10),2)==0)
		gl_FragColor = vec4(0,0.5,1,1);
	else
		gl_FragColor = vec4(0,0,0,1);*/	
}
