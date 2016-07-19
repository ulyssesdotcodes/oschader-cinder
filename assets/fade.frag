uniform sampler2D i_tex_base;
uniform sampler2D i_tex_last;

uniform float i_fade;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  vec4 b = texture(i_tex_base, vertTexCoord0);
  vec4 l = texture(i_tex_last, vertTexCoord0) * i_fade;

  fragColor = b + l * i_fade;
}
