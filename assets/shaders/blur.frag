uniform vec2 i_resolution;
uniform sampler2D i_tex_base;

in vec2 vertTexCoord0;
out vec4 fragColor;

vec4 blur9(sampler2D image, vec2 uv, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.411764705882353) * direction;
  vec2 off2 = vec2(3.2941176470588234) * direction;
  vec2 off3 = vec2(5.176470588235294) * direction;
  color += texture2D(image, uv) * 0.1964825501511404;
  color += texture2D(image, uv + (off1 / i_resolution)) * 0.2969069646728344;
  color += texture2D(image, uv - (off1 / i_resolution)) * 0.2969069646728344;
  color += texture2D(image, uv + (off2 / i_resolution)) * 0.09447039785044732;
  color += texture2D(image, uv - (off2 / i_resolution)) * 0.09447039785044732;
  color += texture2D(image, uv + (off3 / i_resolution)) * 0.010381362401148057;
  color += texture2D(image, uv - (off3 / i_resolution)) * 0.010381362401148057;
  return color;
}

void main() {
  vec2 i;
  vec2 pos = modf(vertTexCoord0, i);

  vec4 bluru = blur9(i_tex_base, pos, vec2(2, 0));
  vec4 bluru2 = blur9(i_tex_base, pos, vec2(4, 0));
  vec4 blurv = blur9(i_tex_base, pos, vec2(0, 2));
  vec4 blurv2 = blur9(i_tex_base, pos, vec2(0, 4));

  fragColor = (bluru + blurv + bluru2 + blurv2) * 0.25;
}
