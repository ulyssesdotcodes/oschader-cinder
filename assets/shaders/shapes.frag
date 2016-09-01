#define PI 3.14159265359
#define TWO_PI 6.28318530718

uniform vec2 i_resolution;
uniform float i_sides;
uniform float i_width;
uniform float i_size;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  vec2 uv = gl_FragCoord.xy / i_resolution.xy - vec2(0.5);
  uv.x *= i_resolution.x / i_resolution.y;

  vec3 color = vec3(0, 0, 0);

  float a = atan(uv.x, uv.y) + PI;
  float r = TWO_PI/max(1, round(i_sides));

  float l = length(uv);
  float d = 1.0 - smoothstep(i_size, i_size + 0.001, cos(floor(.5+a/r)*r - a) * l);
  float e = 1.0 - smoothstep(i_size + i_width, i_size + i_width + 0.001, cos(floor(.5+a/r)*r - a) * l);

  color = vec3(e - d);
  fragColor = vec4(color, 1.0);
}
