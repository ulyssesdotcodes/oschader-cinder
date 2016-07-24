uniform vec2 i_resolution;

uniform sampler2D i_tex_base;
uniform float i_times;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  vec2 i;
  vec2 pos = modf(vertTexCoord0 * (i_times + 1), i);
  vec4 b = texture(i_tex_base, pos);

  fragColor = b;
}
