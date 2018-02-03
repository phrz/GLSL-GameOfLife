uniform sampler2D texture;
uniform sampler2D colormap;

void main() {
	// we assume r,g,b are the same (some shade of gray)
	// and use the r component as the "brightness"
	float level = texture2D(texture, gl_TexCoord[0].xy).r;
	
	// the colormap texture is 256 wide and 1 tall with
	// the colors corresponding to 8-bit black to white
	vec2 colormapCoordinate = vec2(level, 1);
	
	// the resultant color is the pixel at that position
	// in the colormap texture
	gl_FragColor = texture2D(colormap,colormapCoordinate);
}
