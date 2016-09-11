uniform vec2 i_resolution;

uniform sampler2D i_tex_base;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  vec4 b = texture(i_tex_base, vertTexCoord0);

  fragColor = vec4(vec3(1) - b.xyz, b.w);
}
