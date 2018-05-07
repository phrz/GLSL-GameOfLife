#version 120

uniform sampler2D tex;
uniform vec2 resolution;

// get the value of the pixel at the coordinate
// relative to the current pixel
float v(float xrel, float yrel) {
	// gl_TexCoord[0]: fractional coordinate along texture
	// gl_FragCoord:   pixel coordinates (screen)
	vec2 xy;
	xy.x = mod(gl_FragCoord.x + xrel, resolution.x);
	xy.y = mod(gl_FragCoord.y + yrel, resolution.y);
	
	return texture2D(tex, xy/resolution).r;
}

float neighborSum() {
	float a=-1.,b=0.,c=1.;
	return v(a,a)+v(a,b)+v(a,c)+v(b,a)+v(b,c)+v(c,a)+v(c,b)+v(c,c);
}

void main() {
	bool alive = v(0.,0.) == 1.;
	float sum = neighborSum();
	bool b = sum == 3. || (alive && (sum == 2.));
	float a = float(b);
	gl_FragColor = vec4(a, a, a, 1.0);
}
