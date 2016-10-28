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
  vec2 pos = vertTexCoord0;
  //pos.y = 1 - pos.y;
  pos = (pos - vec2(0.5)) * 2;
  vec2 posp = cart2Polar(pos);
  if (pos.x < 0 && pos.y > 0) posp.x += 3.1415;
  if (pos.x < 0 && pos.y < 0) posp.x += 3.1415;
  if (pos.x > 0 && pos.y < 0) posp.x += 6.28318;
  posp.x /= 6.28318;
  fragColor = texture(i_tex_base, posp);
}
