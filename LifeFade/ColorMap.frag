uniform sampler2D texture;
uniform sampler2D colormap;

float random(vec2 co) {
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
	// we assume r,g,b are the same (some shade of gray)
	// and use the r component as the "brightness"
	float level = texture2D(texture, gl_TexCoord[0].xy).r;
	
	// the colormap texture is 256 wide and 1 tall with
	// the colors corresponding to 8-bit black to white
	vec2 colormapCoordinate = vec2(smoothstep(5./255., 1., level), 1);
	
	// the resultant color is the pixel at that position
	// in the colormap texture
	gl_FragColor = texture2D(colormap,colormapCoordinate);
}
