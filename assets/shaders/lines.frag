#define PI 3.14159265359
#define TWO_PI 6.28318530718

uniform vec2 i_resolution;
uniform float i_width;
uniform float i_spacing;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  vec2 uv = gl_FragCoord.xy / i_resolution.xy - vec2(0.5);

  vec3 color = vec3(0, 0, 0);

  float d = round(sin(uv.x * TWO_PI * (1/i_spacing)) * 0.5 + (0.5 * (i_width / i_spacing)));

  color = vec3(d);
  fragColor = vec4(color, 1.0);
}
