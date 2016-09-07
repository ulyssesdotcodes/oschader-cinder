uniform vec2 i_resolution;

uniform sampler2D i_tex_base;
uniform float i_rotate;

in vec2 vertTexCoord0;
out vec4 fragColor;

vec2 cart2Polar(vec2 v) {
  return vec2(atan(v.y, v.x), sqrt(v.x * v.x + v.y * v.y));
}

vec2 polar2Cart(vec2 p) {
  return vec2(p.y * cos(p.x), p.y * sin(p.x));
}

void main() {
  vec2 pos = (vertTexCoord0 - vec2(0.5)) * 2;
  pos = cart2Polar(pos);
  pos.x += i_rotate;
  pos = polar2Cart(pos) * 0.5 + 0.5;
  pos.x = abs(mod(pos.x + 1, 2) - 1);
  pos.y = abs(mod(pos.y + 1, 2) - 1);
  vec4 b = texture(i_tex_base, pos);

  fragColor = b;
}