uniform vec2 i_resolution;

uniform sampler2D tex_base;
uniform float i_scale;

in vec2 vertTexCoord0;

out vec4 fragColor;

void main() {
  vec2 pos = (vertTexCoord0 - vec2(0.5)) * i_scale + vec2(0.5);
  vec4 b = texture(tex_base, pos);

  fragColor = b;
}
