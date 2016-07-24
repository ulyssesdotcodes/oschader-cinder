uniform float i_time;
uniform float i_accumulatedLoudness;

uniform sampler2D i_eqs;
uniform float i_eqs_mod;

in vec2 vertTexCoord0;
out vec4 fragColor;

vec3 hsv2rgb(vec3 c) {
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec2 toCartesian(vec2 p) {
  return vec2(p.y * cos(p.x), p.y * sin(p.x));
}

float iDot(float section, vec2 uv) {

  float l = texture2D(i_eqs, vec2(section, 0.25)).x * 100.0f;

  vec2 cuv = vec2(section * 3.1415 * 2, 0.5);
  vec2 center = toCartesian(cuv);
  float dist = length(center - uv) * 4;

  return smoothstep(l, 0.0, dist * dist * dist);
}

void main() {
  vec2 uv = (vertTexCoord0.xy - vec2(0.5)) * 2.0;
  //vec2 uv = ((2.0 * gl_FragCoord.xy) / i_resolution.xy - vec2(1.0)) * vec2(i_resolution.x/i_resolution.y, 1.0);

  vec3 col = vec3(0.0);
  for(float i = 0.0; i < i_eqs_mod; i++) {
	float seg = i / i_eqs_mod;
    vec3 color = hsv2rgb(vec3(seg, 1.0, 1.0));

    col += iDot(seg, uv) * color * pow(seg + 0.2, 0.5);
  }

  fragColor = vec4(col, 1.0);
}
