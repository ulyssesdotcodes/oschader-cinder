#version 330 core

uniform sampler2D i_tex_audio;

uniform float i_tex_audio_mod;

in vec2 vertTexCoord0;
out vec4 fragColor;

void main() {
	vec2 audio = texture(i_tex_audio, vec2(vertTexCoord0.x, 0.25)).xy;

	float audX = audio.y * (i_tex_audio_mod + 1) + 0.5;

	float clamped = clamp(20 * (0.05 - abs(vertTexCoord0.y - audX)), 0, 1);

	fragColor = vec4(vec3(clamped), 1);
}
