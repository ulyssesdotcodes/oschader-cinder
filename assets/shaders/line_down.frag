uniform float i_time;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  vec2 pos = (vertTexCoord0 + vec2(0.5f)) * 2.0f;

  float y = sin(i_time);

  float color = max(0, (0.1 - (y - pos.y) * (y - pos.y)) * 10);

  fragColor = vec4(color, color, color, 1);
}
