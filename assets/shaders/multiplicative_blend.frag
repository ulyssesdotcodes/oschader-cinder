uniform sampler2D i_tex_base;
uniform sampler2D i_tex_layer;

in vec2 vertTexCoord0;
out vec4 o_fragColor;

void main() {
	vec4 A = texture(i_tex_base, vertTexCoord0);
	vec4 B = texture(i_tex_layer, vertTexCoord0);

	vec3 color = min(vec3(1), A.xyz * B.xyz);

	o_fragColor = vec4(color, 1);
}
