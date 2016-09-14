uniform sampler2D i_tex_base;
uniform sampler2D i_tex_last;

uniform float i_overlay;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
  vec4 b = texture(i_tex_base, vertTexCoord0);
  vec4 l = texture(i_tex_last, vertTexCoord0) * i_overlay;

  if(dot(l.xyz, l.xyz) < 0.01) {
    l.xyz = vec3(0);
  }

  if(dot(b.xyz, b.xyz) < 0.01) {
    b.xyz = l.xyz;
  }

  fragColor = b;
}
