uniform sampler2D i_tex_base;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  fragColor = texture(i_tex_base, vertTexCoord0);
}
