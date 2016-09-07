uniform vec2 i_resolution;

uniform sampler2D i_tex_base;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  vec2 pos = vertTexCoord0;
  vec2 posp = vec2(1) - pos;
  vec4 a = texture(i_tex_base, pos);
  vec4 b = texture(i_tex_base, posp);

  fragColor = a + b;
}
