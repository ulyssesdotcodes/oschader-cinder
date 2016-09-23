uniform vec2 i_resolution;

uniform sampler2D i_tex_base;
uniform float i_scale_x;
uniform float i_scale_y;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  float scale_x = sign(i_scale_x) * max(0.01, abs(1 + i_scale_x));
  float scale_y = sign(i_scale_y) * max(0.01, abs(1 + i_scale_y));
  vec2 pos = (vertTexCoord0 - vec2(0.5)) * (1/vec2(1 + i_scale_x, 1 + i_scale_y)) + vec2(0.5);
  vec4 b = texture(i_tex_base, pos);

  fragColor = b;
}
