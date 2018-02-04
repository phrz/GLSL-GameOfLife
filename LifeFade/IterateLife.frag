uniform sampler2D texture;
uniform vec2 resolution;

// get the value of the pixel at the coordinate
// relative to the current pixel
float v(float xrel, float yrel) {
	// we convert the fractional texture coordinate 0f...1f
	// to integral pixel positions
	vec2 pixelCoord = gl_TexCoord[0].xy * resolution;
	vec2 xy = pixelCoord + vec2(float(xrel),float(yrel));
	
	xy.x = floor(xy.x * 10. + 0.5) / 10.;
	xy.y = floor(xy.y * 12. + 0.5) / 12.;
	
	if(xy.x < 0.) { xy.x += resolution.x; }
	else if(xy.x > resolution.x) { xy.x = mod(xy.x, resolution.x); }

	if(xy.y < 0.) { xy.y += resolution.y; }
	else if(xy.y > resolution.y) { xy.y = mod(xy.y, resolution.y); }
	
	return texture2D(texture, xy/resolution).r;
}

float neighborSum() {
	return v(-1.,-1.) + v(-1.,0.) + v(-1.,1.) + v(0.,-1.) + v(0.,1.) + v(1.,-1.) + v(1.,0.) + v(1.,1.);
}

//return sum == 3 || (isAlive && (sum == 2));
void main() {
	bool alive = floor(v(0.,0.)+0.5) == 1. ? true : false;
	
	float sum = neighborSum();
	float a = float(sum == 3. || (alive && (sum == 2.)));
//	float a = sum / 8.;
	gl_FragColor = vec4(a, a, a, 1.0);
}
