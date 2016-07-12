uniform vec2 i_resolution;
uniform float i_time;
uniform float i_scale;
uniform float i_amplitude;

in vec2 vertTexCoord0;

out vec4 fragColor;

void main() {
  float scale = i_scale + 1.0f; 
  float amplitude = i_amplitude + 1.0f; 
  vec2 pos = 2 * (vertTexCoord0 - vec2(0.5));

  pos = pos * scale;

  float y = sin(pos.x + i_time) * amplitude;

  float color = max(0, (0.1 - (y - pos.y) * (y - pos.y)) * 10);

  fragColor = vec4(color, color, color, 1);
}
