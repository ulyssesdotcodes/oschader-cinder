uniform vec2 i_resolution;
uniform float i_time;

out vec4 fragColor;

void main() {
  vec2 pos = (gl_FragCoord.xy / i_resolution.xy - vec2(0.5)) * vec2(i_resolution.x/i_resolution.y, 1.0);

  float y = sin(i_time);

  float color = max(0, (0.1 - (y - pos.y) * (y - pos.y)) * 10);

  fragColor = vec4(color, color, color, 1);
}
