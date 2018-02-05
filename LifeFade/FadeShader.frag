#version 120

uniform sampler2D texture;

void main() {
	vec4 color = texture2D(texture, gl_TexCoord[0].xy);
//	int r = int(floor(color.r * 255.)) + 10;
//	float f = float(r)/255.;
	gl_FragColor = vec4(color.rgb, color.r+0.01);
}
