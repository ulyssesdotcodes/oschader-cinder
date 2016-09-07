uniform vec2 i_resolution;

uniform sampler2D i_tex_base;
uniform float i_translate_x;
uniform float i_translate_y;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  vec2 translate = vec2(i_translate_x, i_translate_y);
  translate.x *= i_resolution.y / i_resolution.x;
  vec2 pos = vertTexCoord0 + translate;
  pos.x = abs(mod(pos.x + 1, 2) - 1);
  pos.y = abs(mod(pos.y + 1, 2) - 1);
  vec4 b = texture(i_tex_base, pos);

  fragColor = b;
}
