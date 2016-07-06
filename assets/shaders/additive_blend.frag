#version 330 core


uniform sampler2D i_tex_A;
uniform sampler2D i_tex_B;

uniform vec2 i_resolution;

out vec4 o_fragColor;

void main() {
	vec2 pos = gl_FragCoord.xy / i_resolution.xy;
	vec4 A = texture2D(i_tex_A, pos);
	vec4 B = texture2D(i_tex_B, pos);

	vec3 color = min(vec3(1), A.xyz + B.xyz);

	o_fragColor = vec4(color, 1);
}
