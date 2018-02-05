#version 120

uniform sampler2D texture;

void main() {
	float fadeRate = 0.01;
	vec4 color = texture2D(texture, gl_TexCoord[0].xy);
	gl_FragColor = vec4(color.rgb, color.r + fadeRate);
}
