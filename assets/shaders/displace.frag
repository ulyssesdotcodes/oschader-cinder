uniform sampler2D i_tex_base;
uniform sampler2D i_tex_layer;

in vec2 vertTexCoord0;
out vec4 o_fragColor;

void main() {
	vec4 displace = texture(i_tex_layer, vertTexCoord0);
	vec4 A = texture(i_tex_base, vertTexCoord0 + displace.xy);

	o_fragColor = A;
}
