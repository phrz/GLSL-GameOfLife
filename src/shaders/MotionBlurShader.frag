uniform sampler2D texture;

void main() {
	vec3 color = texture2D(texture, gl_TexCoord[0].xy).rgb;
	gl_FragColor = vec4(color, 0.1);
}
